# Aplicativo de Clima para Terminal em C++

![C++](https://img.shields.io/badge/language-C%2B%2B-blue.svg)
![Platform](https://img.shields.io/badge/platform-Windows-brightgreen.svg)
![License](https://img.shields.io/badge/license-MIT-lightgrey.svg)

Este é um projeto de um aplicativo de console para consulta de previsão do tempo, desenvolvido como parte do Projeto Integrador da faculdade. O programa é escrito em C++ e utiliza APIs externas para fornecer dados climáticos em tempo real e previsões futuras diretamente no terminal.

---

## 🚀 Funcionalidades

* **Clima Atual:** Exibe informações detalhadas sobre o clima atual da cidade selecionada, incluindo:
    * Temperatura e sensação térmica.
    * Condição do tempo (ex: "céu limpo", "chuva leve").
    * Temperatura mínima e máxima do dia.
    * Umidade, velocidade do vento e pressão atmosférica.
* **Previsão para 5 Dias:** Mostra um resumo da previsão para os próximos cinco dias.
* **Busca por Cidade:** Permite ao usuário buscar pelo clima de qualquer cidade do mundo.
* **Cidade Favorita:** Salva a última cidade pesquisada em um arquivo local (`cidade.txt`) para acesso rápido.
* **Interface Colorida:** Utiliza cores no terminal para uma experiência de usuário mais agradável e intuitiva.
* **Consumo de API Real:** Conecta-se diretamente à API do [OpenWeatherMap](https://openweathermap.org/api) para obter dados precisos e em tempo real.

---

## 🛠️ Tecnologias Utilizadas

* **Linguagem:** C++
* **Bibliotecas:**
    * **libcurl:** Para realizar as requisições HTTP e se conectar com a API.
    * **nlohmann/json:** Para processar ("parsear") a resposta JSON da API de forma eficiente.
* **Compilador (Ambiente Windows):** MinGW-w64 (g++)
* **IDE:** Visual Studio Code

---

## ⚙️ Pré-requisitos e Instalação

Para compilar e executar este projeto em um ambiente Windows, você precisará de:

1.  **Compilador g++:** Recomendamos o [MinGW-w64](https://www.mingw-w64.org/downloads/). Certifique-se de adicionar o caminho da pasta `bin` às variáveis de ambiente do Windows.
2.  **Biblioteca libcurl:** Baixe a versão para MinGW no [site oficial](https://curl.se/windows/) e extraia para um local de fácil acesso (ex: `C:\libs\curl`).
3.  **Biblioteca nlohmann/json:** Baixe o arquivo de cabeçalho único `json.hpp` do [repositório no GitHub](https://github.com/nlohmann/json/releases/latest/download/json.hpp).

### Passos para Configuração

1.  **Clone o repositório:**
    ```bash
    git clone [https://github.com/seu-usuario/seu-repositorio.git](https://github.com/seu-usuario/seu-repositorio.git)
    cd seu-repositorio
    ```

2.  **Adicione as bibliotecas:**
    * Coloque o arquivo `json.hpp` dentro de uma pasta `include` na raiz do projeto.
    * Certifique-se de que a `libcurl` está em um caminho conhecido (ex: `C:\libs\curl`).

3.  **Obtenha uma Chave de API:**
    * Crie uma conta gratuita no site [OpenWeatherMap](https://openweathermap.org/home/sign_up).
    * Acesse seu painel e copie sua chave de API (API Key).
    * No arquivo `main.cpp`, substitua o texto `"SUA_API_KEY_AQUI"` pela sua chave real. **Atenção:** a chave precisa ser inserida em duas funções diferentes no código.

4.  **Copie a DLL:**
    * Copie o arquivo `libcurl-x64.dll` (que está na pasta `bin` da `libcurl`) e cole na pasta principal do seu projeto, ao lado de onde o executável será criado.

5.  **Compile o projeto:**
    * Abra um terminal na pasta do projeto e execute o seguinte comando para criar o programa `clima.exe`:
    ```bash
    g++ main.cpp -o clima.exe -I"C:/libs/curl/include" -L"C:/libs/curl/lib" -lcurl
    ```
    *(Lembre-se de ajustar o caminho para a `libcurl` se você a salvou em um lugar diferente de `C:\libs\curl`)*

---

## ▶️ Como Usar

Após a compilação bem-sucedida, o arquivo `clima.exe` será criado na pasta principal. Para executar o programa, simplesmente digite no terminal:

```bash
./clima.exe
