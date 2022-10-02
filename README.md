# Calculadora Runge Kutta
Esse repositório tem como objetivo a entrega da atividade "Novo Algoritmo de Rouge-Kutta", referente a matéria de Cálculo para Computação (ECP03_T01).

O sistema base conta com um "console" capaz de receber comandos. A fim de separar os comandos logicamente, uma estrutura chamada `Screen` foi criada, e é manuseada pela classe `Application`. Para essa interação, foi utilizado o padrão de design de [State](https://refactoring.guru/design-patterns/state).

Para o cálculo do RK4, um passo adicional teve de ser efetuado a fim de que uma função determinada pelo usuário fosse aceita. Primeiro, o programa recebe a entrada do usuário e a "quebra" em `Tokens`. Cada token tem um tipo, ordem de precedência, e outras informações. Esses tokens são então enviados para o `Parser` - uma implementação do algoritmo [Shunting yard](https://en.wikipedia.org/wiki/Shunting_yard_algorithm), inventado por Edsger Dijkstra. Esse algoritmo transforma a sequência de tokens em notação de posfixo. Com esses resultados, o algoritmo utiliza uma função de interpretação - um "Postfix stack evaluator". Essa função é utilizada pelas funções do RK4, para por fim gerar o resultado final. Esse princípio é similar ao utilizado por [linguagens interpretadas](https://en.wikipedia.org/wiki/Interpreter_(computing)).

## Equipe
Como especificado, essa atividade foi realizada individualmente. Entretanto, para fins de validação da minha personalidade, subscrevo abaixo minha conta e meu nome.
 * [Paulo V. Castro G.](https://github.com/DatDarkAlpaca)

# Instalação
É possível obter uma versão do algoritmo buildada na seção de Releases. Caso queira contribuir para o projeto, siga os passos abaixo.

## Pré-requisitos
Esse projeto **não** conta com um sistema de geração de projetos, tendo em vista seu escopo limitado. Para contribuir, você precisará instalar o Visual Studio, ou criar seu próprio sistema de geração de projetos.

 * [Visual Studio Community](https://visualstudio.microsoft.com/pt-br/vs/community/)
 * (Opcional) [Git](https://git-scm.com/downloads)

## Download
A fim de acessar os arquivos do projeto, primeiro você deve baixá-los. A opção mais adequada é cloná-lo utilizando o git. Entretanto, você também pode baixar o projeto clicando [aqui](https://github.com/leomartins98/Sexshop-System/archive/refs/heads/main.zip). Para clonar o repositório em sua máquina, utilize o seguinte comando:

```
git clone https://github.com/DatDarkAlpaca/runge-kutta
```

## Execução
Tendo instalado o [Visual Studio](https://visualstudio.microsoft.com/pt-br/vs/community/), basta abrir o arquivo de solução `runge-kutta.sln` e pressionar `F5` para inicializar a aplicação.

# Licença
Esse projeto é licenciado sob a [The Unlicense](https://github.com/DatDarkAlpaca/runge-kutta/blob/main/LICENSE) - veja o arquivo de [Licença](LICENSE) para mais detalhes.
