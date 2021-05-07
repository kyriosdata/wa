# wa

WebAssembly permite escrever módulos "rápidos", ou WASM, para ser executado em um navegador a partir de linguagens como C e C++, dentre outras. Ou seja, é uma busca por eficiência do código executado em um navegador.

Neste processo é necessário criar tais módulos a partir de lingagens como Rust, C, C++ ou Kotlin, por exemplo, e permitir que código em um módulo em WebAssemly possa interagir com código em JavaScrit.

A interação entre código escrito em JavaScript e C é facilitada por
ferramentas como [emscripten](https://emscripten.org/) que oferece
vários recursos tanto para o código em JavaScript quanto para o código em C.

## Pré-requisitos

- Editor (por exemplo, VS Code)
  - [WasmFiddle](https://wasdk.github.io/WasmFiddle/)
  - [Linguagem C](https://www.programiz.com/c-programming)
- Chrome
- node (e npm)
- Aplicação Express para disponibilizar diretório para o browser
- Git
- NodeJS
- Python
- CMake

## emscripten (instalação)

- Devidamente documentado em https://emscripten.org/docs/getting_started/downloads.html

## Compilar

- `emcc lib/demo.c -s WASM=1 -O3 -o demo.js`
- `emcc lib/demo.c -s WASM=1 -O3 --pre-js antes.js -o demo.js`
- `emcc lib/demo.c -s WASM=1 -O3 --post-js apos.js -o demo.js`

## Promt

- Onde foi decidido para depositar o emscripten encontra-se `emsdk_env.bat` empregado para definir as variáveis de ambiente exigidas para acesso aos vários programas que fazem parte deste SDK.

## Alguns links

- [WebAssembly.instantiateStreaming()](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/WebAssembly/instantiateStreaming)

## WebAssembly a partir de código em C

- Todas as funções no código em C compilado em WASM tornam-se
  disponíveis para uso via código em JavaScript. Este código em C
  pode fazer uso de funções da biblioteca básica de C. São os
  _exports_.

- Função importada deve ser declarada no código em C, por exemplo,
  `void log(char* str)` para função que recebe uma sequência de
  caracteres como argumento. O código em C chamará esta função como
  `log("casa")`, por exemplo. Além da declaração no código em C é
  necessário passar um objeto, segundo argumento, ao método
  `instantiateStreaming`. Desta forma, ao contrário do caso anterior,
  nem toda função em JavaScript estará disponível ao módulo, mas apenas aquelas explicitamente indicadas pelo segundo argumento. Abaixo segue como definir um objeto para este segundo argumento, no
  qual indica que o módulo em questão fará usa função `log` cuja
  implementação em JavaScript é `console.log`.

```js
const imports = {
  env: {
    log: console.log,
  },
};
```

- Como uma sequência de caracteres é passada de C para JavaScript?
  Por meio de um apontador (um deslocamento em uma memória, ou _offset_). Desta forma, ao usar a função acima será exibido este
  deslocamento, em vez da sequência propriamente dita. Para recuperar
  os dados é necessário acesso à memória do WASM.

- Função importada que passa uma sequência de caracteres

- Funções que recebem como argumento ou retornam apontadores
  precisam de tratamento específico em C. Por enquanto, ocorre erro,
  ou seja, não consigo passar dados como uma string.
