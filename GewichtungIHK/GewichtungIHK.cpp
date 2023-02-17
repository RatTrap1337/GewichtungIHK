#include <windows.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>

static std::unordered_map<std::string, std::string> DynData;

void Pad(int Offset) noexcept {

    for (int i = 0; i < Offset; i++) {
        std::cout << "    ";
    }
}

void Title(const std::string& Title, int Pad = 0) noexcept {

    if (Pad) {

        ::Pad(Pad);
    }

    std::cout << Title << "\n";
}

template <typename Type>
void Input(const std::string& Text, Type& Value, int Pad = 1) noexcept {

    if (Pad) {

        ::Pad(Pad);
    }

    std::cout << Text;
    std::cin >> Value;
}

template <typename Type>
Type GetValue(const std::string& Value) {

    if (typeid(Type).hash_code() == typeid(float).hash_code()) {

        return static_cast<float>(atoi(Value.c_str()));
    }

    return Type();
}

#define GVF(x) GetValue<float>(DynData[x])

void CalculateResult() noexcept {

    const auto ResT1 = GVF("t1pb1") * 0.2f;
    const auto ResTA = GVF("t2tapb2") * 0.5f;
    const auto ResPB3 = GVF("t2tbpb3") * 0.1f;
    const auto ResPB4 = GVF("t2tbpb4") * 0.1f;
    const auto ResPB5 = GVF("t2tbpb5") * 0.1f;
    const auto ResTB = (ResPB3 + ResPB4 + ResPB5);
    const auto ResT2 = (ResTA + ResTB);
    const auto ResMep = GVF("mep1");
    const auto ResTotal = (ResT1 + ResT2) * 2.f;
    const auto ResOverall = (ResMep + ResTotal) / 3.f;
    const auto Passed = (ResOverall >= 50.f);

    std::cout << "\nSie haben die Prüfung mit " << std::setprecision(2) << ResTotal << "% " << (Passed ? "" : "nicht") << " bestanden.\n" << std::endl;
}

int main() {

    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    SetConsoleTitleA("Gewichtung IHK (Fachinformatik)");

    Title("[Erster Teil] (20%)");

    Input("Prüfungsbereich 1 (20%): ", DynData["t1pb1"]);

    Title("[Zweiter Teil] (80%)");
    Title("[Teil A] (50%)", 1);

    Input("Prüfungsbereich 2 (50%): ", DynData["t2tapb2"], 2);

    Title("[Teil B] (30%)", 1);

    Input("Prüfungsbereich 3 (10%): ", DynData["t2tbpb3"], 2);
    Input("Prüfungsbereich 4 (10%): ", DynData["t2tbpb4"], 2);
    Input("Prüfungsbereich 5 (10%): ", DynData["t2tbpb5"], 2);

    Title("[Optionaler Teil] (2:1)");

    Input("Mündliche Ergänzungsprüfung (2:1): ", DynData["mep1"]);

    CalculateResult();

    return system("pause");
}

