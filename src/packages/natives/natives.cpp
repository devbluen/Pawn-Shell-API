
#include "packages/natives/natives.hpp"
#include "packages/functions/utf8fix.hpp"

bool Script::OnLoad() {
    int num_publics{};
    amx_->NumPublics(&num_publics);

    auto &plugin = Plugin::Instance();    

    for(int index{}; index < num_publics; index++) {
        std::string public_name = GetPublicName(index);
        m_publics[public_name] = MakePublic(public_name, plugin.UseCaching());
    }
    return true;
}

bool Plugin::OnLoad() {
    RegisterNative<&Script::n_ShellExec>("ShellExec");
    return true;
}

cell Script::n_ShellExec(std::string command, std::string callback) {
    std::thread t([this, command, callback]() {
        this->ExecuteAsync(command, callback);
    });
    
    t.detach();
    return true; 
}



/*

                    ooooooooo.   ooooooooo.   ooooo oooooo     oooo       .o.       ooooooooooooo oooooooooooo 
                    `888   `Y88. `888   `Y88. `888'  `888.     .8'       .888.      8'   888   `8 `888'     `8 
                    888   .d88'  888   .d88'  888    `888.   .8'       .8"888.          888       888         
                    888ooo88P'   888ooo88P'   888     `888. .8'       .8' `888.         888       888oooo8    
                    888          888`88b.     888      `888.8'       .88ooo8888.        888       888    "    
                    888          888  `88b.   888       `888'       .8'     `888.       888       888       o 
                    o888o        o888o  o888o o888o       `8'       o88o     o8888o     o888o     o888ooooood8 
                                                                                                            
                    .o88o.                                       .    o8o                                     
                    888 `"                                     .o8    `"'                                     
                    o888oo  oooo  oooo  ooo. .oo.    .ooooo.  .o888oo oooo   .ooooo.  ooo. .oo.    .oooo.o     
                    888    `888  `888  `888P"Y88b  d88' `"Y8   888   `888  d88' `88b `888P"Y88b  d88(  "8     
                    888     888   888   888   888  888         888    888  888   888  888   888  `"Y88b.      
                    888     888   888   888   888  888   .o8   888 .  888  888   888  888   888  o.  )88b     
                    o888o    `V88V"V8P' o888o o888o `Y8bod8P'   "888" o888o `Y8bod8P' o888o o888o 8""888P'     

*/

void Script::ExecuteAsync(std::string command, std::string callback) {
    std::string output;
    std::array<char, 128> buffer;
    
#ifdef _WIN32
    std::string finalCommand = "powershell -Command \"" + command + "\"";
    auto pipe = _popen(finalCommand.c_str(), "r");
#else
    std::string finalCommand = command;
    auto pipe = popen(finalCommand.c_str(), "r");
#endif

    if (pipe) {
        while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
            output += buffer.data();
        }
#ifdef _WIN32
        int result = _pclose(pipe);
#else
        int result = pclose(pipe);
#endif

        if (!callback.empty()) {
            auto it = m_publics.find(callback);
            if (it != m_publics.end() && it->second && it->second->Exists()) {
                it->second->Exec(result, output);
            }
        }
    }
}