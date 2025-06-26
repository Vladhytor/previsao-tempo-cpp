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
    * **libcurl:** Para realizar as requisições HTTP e
