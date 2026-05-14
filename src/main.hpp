
#pragma once
#define _GLIBCXX_USE_CXX11_ABI 1

    // Main Includes
#include <string>
#include <cstdarg>

    // Includes
#include <sdk.hpp>
#include "Server/Components/Pawn/pawn.hpp"
#include "samp-ptl/ptl.h"
#include "cpptoml/include/cpptoml.h"

#ifdef THISCALL
#undef THISCALL
#endif

#ifdef _WIN32
#define THISCALL __thiscall
#else
#define THISCALL
#endif

    // Misc
#include "packages/natives/natives.hpp"
#include "packages/logs/logs.hpp"

class PluginComponent final : 
                    public IComponent,
                    public PawnEventHandler,
                    public PlayerConnectEventHandler,
                    public PlayerDamageEventHandler
                {

    public:
        PROVIDE_UID(0xEC77BF5A19BEF0C8);

        StringView componentName() const override { return "ShellAPI"; }
        SemanticVersion componentVersion() const override { return { 1, 0, 3, 6 }; }
        void onLoad(ICore* core) override;
        void onInit(IComponentList* components) override;
        void onReady() override;
        void onFree(IComponent* component) override;
        void free() override;
        void reset() override;

        static void PluginLogprintf(const char *fmt, ...);
        static ICore *&getCore();

        void onAmxLoad(IPawnScript& script) override;
        void onAmxUnload(IPawnScript& script) override;

    private:
        ICore* gCore = nullptr;
        IPlayerPool *gPlayers{};
        IPawnComponent *gPawnComponents{};
        void *gPluginData[MAX_PLUGIN_DATA]{};
};
