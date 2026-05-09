class ShildGuard final
    : public IComponent
    , public PawnEventHandler
    , public PlayerConnectEventHandler
    , public PlayerSpawnEventHandler
    , public PlayerTextEventHandler {

public:
    
    // ── Eventos ───────────────────────────────────────────────────────────────

    void onPlayerConnect(IPlayer& player) override {
        gCore->logLn(LogLevel::Message, "[ShildGuard] %s (ID %d) conectou.",
            player.getName().data(), player.getID());
        EnviarMensagem(player, Colour(255, 220, 0, 255), "Bem-vindo ao servidor!");
        std::string aviso = std::string(player.getName().data()) + " entrou no servidor.";
        EnviarMensagemGlobal(Colour(200, 200, 200, 255), aviso.c_str());
    }

    void onPlayerDisconnect(IPlayer& player, PeerDisconnectReason reason) override {
        gCore->logLn(LogLevel::Message, "[ShildGuard] %s desconectou.", player.getName().data());
    }

    void onPlayerSpawn(IPlayer& player) override {
        EnviarMensagem(player, Colour(100, 255, 100, 255), "Voce spawnnou! Use /ajuda.");
        DarDinheiro(player, 500);
    }

    // Intercepta o chat para simular /comandos.
    // Retornar true  = suprime a mensagem do chat (comando tratado)
    // Retornar false = mensagem aparece normalmente no chat
    bool onPlayerText(IPlayer& player, StringView message) override {
        std::string msg(message.data(), message.length());

        if (msg.empty() || msg[0] != '/') return false;

        if (msg == "/ajuda") {
            EnviarMensagem(player, Colour(255, 220, 100, 255), "=== Comandos ===");
            EnviarMensagem(player, Colour(255, 255, 255, 255), "/ajuda    - Esta lista");
            EnviarMensagem(player, Colour(255, 255, 255, 255), "/posicao  - Sua posicao atual");
            EnviarMensagem(player, Colour(255, 255, 255, 255), "/tele     - Teleporta ao centro");
            return true;
        }

        if (msg == "/posicao") {
            if (!JaSpawnou(player)) {
                EnviarMensagem(player, Colour(255, 80, 80, 255), "Voce ainda nao spawnnou!");
                return true;
            }
            Vector3 pos = player.getPosition();
            char buffer[128];
            snprintf(buffer, sizeof(buffer), "Posicao: X=%.2f  Y=%.2f  Z=%.2f", pos.x, pos.y, pos.z);
            EnviarMensagem(player, Colour(100, 200, 255, 255), buffer);
            return true;
        }

        if (msg == "/tele") {
            if (!JaSpawnou(player)) {
                EnviarMensagem(player, Colour(255, 80, 80, 255), "Spawne antes de usar este comando!");
                return true;
            }
            Teleportar(player, 0.0f, 0.0f, 3.0f);
            EnviarMensagem(player, Colour(255, 255, 0, 255), "Teleportado para o centro!");
            return true;
        }

        EnviarMensagem(player, Colour(255, 80, 80, 255), "Comando desconhecido. Use /ajuda.");
        return true;
    }
};




void EnviarMensagem(IPlayer& player, Colour cor, const char* texto) {
    player.sendClientMessage(cor, texto);
}

void EnviarMensagemGlobal(Colour cor, const char* texto) {
    if (!gCore) return;
    for (IPlayer* p : gCore->getPlayers().entries()) {
        p->sendClientMessage(cor, texto);
    }
}

// Estado do jogador.
// getState() retorna: 0=None, 1=OnFoot, 2=Driver, 3=Passenger, 7=Wasted
bool JaSpawnou(IPlayer& player) {
    int estado = static_cast<int>(player.getState());
    return estado != 0 && estado != 7;
}

void DarDinheiro(IPlayer& player, int quantidade) {
    player.giveMoney(quantidade);
}

void Teleportar(IPlayer& player, float x, float y, float z) {
    player.setPosition({ x, y, z });
}