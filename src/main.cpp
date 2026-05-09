
        // Utils
#include "main.hpp"

void PluginComponent::onLoad(ICore* core) {}

void PluginComponent::onInit(IComponentList* components) {
    gPawnComponents = components->queryComponent<IPawnComponent>();

    if(!gPawnComponents) {
        StringView name = componentName();
        Log::Write(LogLevel::Error, "Error loading component %.*s: Pawn component not loaded", name.length(), name.data());
        return;
    }
    
    gPawnComponents->getEventDispatcher().addEventHandler(this);
    gPluginData[PLUGIN_DATA_LOGPRINTF] = reinterpret_cast<void*>(&PluginLogprintf);
    gPluginData[PLUGIN_DATA_AMX_EXPORTS] = const_cast<void**>(gPawnComponents->getAmxFunctions().data());

    if (!Plugin::DoLoad(gPluginData)) {
        Log::Write(LogLevel::Error, "Plugin::DoLoad failed");
        return;
    }
}

void PluginComponent::onFree(IComponent* component) {

    if (component == gPawnComponents || component == this) {
        Plugin::DoUnload();

        if (gPawnComponents) 
            gPawnComponents->getEventDispatcher().removeEventHandler(this);

        gPawnComponents = nullptr;
    }
}

void PluginComponent::free() {
    delete this;
}

void PluginComponent::onReady() {}

ICore *&PluginComponent::getCore() {
    static ICore *core{};
    return core;
}

void PluginComponent::reset() {}

void PluginComponent::onAmxLoad(IPawnScript &script) {
    Plugin::DoAmxLoad(static_cast<AMX *>(script.GetAMX()));
};

void PluginComponent::onAmxUnload(IPawnScript &script) {
    Plugin::DoAmxUnload(static_cast<AMX *>(script.GetAMX()));
};

void PluginComponent::PluginLogprintf(const char *fmt, ...) {
    auto core = getCore();
    if (!core) 
        return;

    va_list args{};
    va_start(args, fmt);
    core->vprintLn(fmt, args);
    va_end(args);
}

COMPONENT_ENTRY_POINT() { return new PluginComponent(); }