#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>
#include <windows.h>
#include <curl/curl.h>
#include "include/json.hpp"

using json = nlohmann::json;
using namespace std;

// --- NOVAS CONSTANTES DE CORES ---
const string COR_CIANO = "\033[36m";
const string COR_AMARELO = "\033[33m";
const string COR_VERDE = "\033[32m";
const string COR_BRANCO = "\033[37m";
const string COR_RESET = "\033[0m"; // Reseta para a cor padrão

struct Clima {
    string cidade;
    double temperaturaAtual;
    double sensacaoTermica;
    string condicao;
    int umidade;
    double tempMin;
    double tempMax;
    double ventoVelocidade;
    int pressao;
};

struct PrevisaoFutura {
    string dataHora;
    double temperatura;
    string condicao;
};

// --- NOVA FUNÇÃO ---
// Ativa o suporte para cores no terminal do Windows
void ativarCoresNoTerminal() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

size_t writeCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

bool buscarClimaAtualAPI(Clima& clima) {
    CURL* curl; CURLcode res; string respostaJson; bool sucesso = false;
    cout << "\nBuscando dados atuais para '" << clima.cidade << "' na API..." << endl;
    curl = curl_easy_init();
    if (curl) {
        string apiKey = "b0487a37bcfedce23491a4f81701f754";
        char* cidade_escaped = curl_easy_escape(curl, clima.cidade.c_str(), clima.cidade.length());
        if(cidade_escaped) {
            string url = "https://api.openweathermap.org/data/2.5/weather?q=" + string(cidade_escaped) + "&appid=" + apiKey + "&lang=pt_br&units=metric";
            curl_free(cidade_escaped);
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &respostaJson);
            res = curl_easy_perform(curl);
            if (res == CURLE_OK) {
                try {
                    json data = json::parse(respostaJson);
                    if (data.contains("cod") && data["cod"] != 200) { cout << COR_AMARELO << "Erro da API: " << data["message"] << COR_RESET << endl; } else {
                        clima.temperaturaAtual = data["main"]["temp"];
                        clima.sensacaoTermica = data["main"]["feels_like"];
                        clima.condicao = data["weather"][0]["description"];
                        clima.umidade = data["main"]["humidity"];
                        clima.tempMin = data["main"]["temp_min"];
                        clima.tempMax = data["main"]["temp_max"];
                        clima.pressao = data["main"]["pressure"];
                        clima.ventoVelocidade = (data["wind"]["speed"].get<double>() * 3.6);
                        sucesso = true;
                    }
                } catch (json::parse_error& e) { cerr << "Erro ao processar o JSON: " << e.what() << endl; }
            } else { cerr << "Erro na requisição da API: " << curl_easy_strerror(res) << endl; }
        }
        curl_easy_cleanup(curl);
    }
    return sucesso;
}

bool buscarPrevisao5DiasAPI(const string& cidade, vector<PrevisaoFutura>& previsoes) {
    CURL* curl; CURLcode res; string respostaJson; bool sucesso = false;
    cout << "\nBuscando previsão para os próximos dias..." << endl;
    curl = curl_easy_init();
    if (curl) {
        string apiKey = "b0487a37bcfedce23491a4f81701f754";
        char* cidade_escaped = curl_easy_escape(curl, cidade.c_str(), cidade.length());
        if (cidade_escaped) {
            string url = "https://api.openweathermap.org/data/2.5/forecast?q=" + string(cidade_escaped) + "&appid=" + apiKey + "&lang=pt_br&units=metric";
            curl_free(cidade_escaped);
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &respostaJson);
            res = curl_easy_perform(curl);
            if (res == CURLE_OK) {
                try {
                    json data = json::parse(respostaJson);
                    if (data.contains("cod") && data["cod"] != "200") { cout << COR_AMARELO << "Erro da API: " << data["message"] << COR_RESET << endl; } else {
                        previsoes.clear();
                        for (const auto& item : data["list"]) {
                            string dataHora = item["dt_txt"];
                            if (dataHora.find("12:00:00") != string::npos) {
                                PrevisaoFutura p;
                                p.dataHora = dataHora.substr(0, 10);
                                p.temperatura = item["main"]["temp"];
                                p.condicao = item["weather"][0]["description"];
                                previsoes.push_back(p);
                            }
                        }
                        sucesso = true;
                    }
                } catch (json::parse_error& e) { cerr << "Erro ao processar o JSON: " << e.what() << endl; }
            } else { cerr << "Erro na requisição da API: " << curl_easy_strerror(res) << endl; }
        }
        curl_easy_cleanup(curl);
    }
    return sucesso;
}

// ATUALIZADO com cores
void exibirPrevisaoAtual(const Clima& clima) {
    cout << COR_CIANO << "\n===== PREVISÃO ATUAL PARA " << clima.cidade << " =====" << COR_RESET << endl;
    cout << COR_BRANCO << "Condição: " << COR_AMARELO << clima.condicao << COR_RESET << endl;
    cout << COR_BRANCO << "Temperatura: " << COR_AMARELO << clima.temperaturaAtual << " C" << COR_RESET << endl;
    cout << COR_BRANCO << "Sensação Térmica: " << COR_AMARELO << clima.sensacaoTermica << " C" << COR_RESET << endl;
    cout << COR_BRANCO << "Temp. Mínima: " << COR_AMARELO << clima.tempMin << " C" << COR_RESET << endl;
    cout << COR_BRANCO << "Temp. Máxima: " << COR_AMARELO << clima.tempMax << " C" << COR_RESET << endl;
    cout << COR_BRANCO << "Umidade: " << COR_AMARELO << clima.umidade << "%" << COR_RESET << endl;
    cout << COR_BRANCO << "Velocidade do Vento: " << COR_AMARELO << clima.ventoVelocidade << " km/h" << COR_RESET << endl;
    cout << COR_BRANCO << "Pressão Atmosférica: " << COR_AMARELO << clima.pressao << " hPa" << COR_RESET << endl;
}

// ATUALIZADO com cores
void exibirPrevisao5Dias(const vector<PrevisaoFutura>& previsoes) {
    cout << COR_CIANO << "\n===== PREVISÃO PARA OS PRÓXIMOS DIAS (AO MEIO-DIA) =====" << COR_RESET << endl;
    for (const auto& p : previsoes) {
        cout << COR_BRANCO << "Data: " << COR_VERDE << p.dataHora
             << COR_BRANCO << " | Temp: " << COR_AMARELO << p.temperatura << " C"
             << COR_BRANCO << " | Condição: " << COR_AMARELO << p.condicao << COR_RESET << endl;
    }
}

void carregarCidadeFavorita(string& cidade) {
    ifstream arquivoEntrada("cidade.txt");
    if (arquivoEntrada.is_open()) { getline(arquivoEntrada, cidade); arquivoEntrada.close(); }
    else { cidade = "Brasilia"; }
}

void alterarCidadeFavorita(string& cidade) {
    cout << "Digite o nome da nova cidade: ";
    getline(cin, cidade);
    ofstream arquivoSaida("cidade.txt");
    arquivoSaida << cidade;
    arquivoSaida.close();
    cout << COR_VERDE << "Cidade favorita '" << cidade << "' salva com sucesso!" << COR_RESET << endl;
}

int main() {
    ativarCoresNoTerminal(); // Ativa as cores!
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "Portuguese");

    Clima clima;
    vector<PrevisaoFutura> previsoes5dias;
    string escolha;

    carregarCidadeFavorita(clima.cidade);

    do {
        cout << COR_CIANO << "\n=== APLICATIVO DE CLIMA ===" << COR_RESET << endl;
        cout << COR_BRANCO << "Cidade atual: " << COR_VERDE << clima.cidade << COR_RESET << endl;
        cout << "[1] Ver previsão ATUAL" << endl;
        cout << "[2] Ver previsão para os PRÓXIMOS DIAS" << endl;
        cout << "[3] Alterar cidade favorita" << endl;
        cout << "[0] Sair" << endl;
        cout << COR_BRANCO << "Escolha uma opção: " << COR_RESET;
        getline(cin, escolha);

        if (escolha == "1") {
            if (buscarClimaAtualAPI(clima)) { exibirPrevisaoAtual(clima); }
        } else if (escolha == "2") {
            if (buscarPrevisao5DiasAPI(clima.cidade, previsoes5dias)) { exibirPrevisao5Dias(previsoes5dias); }
        } else if (escolha == "3") {
            alterarCidadeFavorita(clima.cidade);
        } else if (escolha != "0") {
            cout << COR_AMARELO << "Opção inválida. Tente novamente." << COR_RESET << endl;
        }

    } while (escolha != "0");

    cout << COR_VERDE << "\nObrigado por usar o aplicativo de clima!" << COR_RESET << endl;
    return 0;
}