
#pragma once
#include <sdk.hpp>
#include <cstdlib>
#include <thread>
#include <map>
#include <future>
#include "samp-ptl/ptl.h"

using PublicPtr = std::shared_ptr<ptl::Public>;

class Script : public ptl::AbstractScript<Script> {
    public:
        const char *VarVersion() { return "_shellapi_version"; }
        const char *VarIsGamemode() { return "_shellapi_gamemode"; }

        bool OnLoad();
        cell n_ShellExec(std::string command, std::string callback);
        
    private:
        void ExecuteAsync(std::string command, std::string callback);
        std::map<std::string, PublicPtr> m_publics;
};

class Plugin : public ptl::AbstractPlugin<Plugin, Script> {
    public:
        const char *Name() { return "ShellAPI"; }

        bool UseCaching() const { return use_caching_; }
        bool OnLoad();

    private:
        bool use_caching_{};
};