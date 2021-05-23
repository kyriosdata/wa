# wa

WebAssembly permite escrever módulos "rápidos", ou WASM, para ser executado em um navegador a partir de linguagens como C e C++, dentre outras. Ou seja, é uma busca por eficiência do código executado em um navegador.

Neste processo é necessário criar tais módulos a partir de lingagens como Rust, C, C++ ou Kotlin, por exemplo, permitir que este código seja chamado por código em JavaScript e, adicionalmente, permitir que código em um módulo em WebAssemly possa chamar código em JavaScrit.

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
- Execute no diretório de instalação `emsdk_env.bat` ou correspondente para preparação de variáveis de ambiente empregadas.

## Prompt

- Onde foi decidido para depositar o emscripten encontra-se `emsdk_env.bat` empregado para definir as variáveis de ambiente exigidas para acesso aos vários programas que fazem parte deste SDK.

## Elementos básicos

- É preciso uma página HTML que irá chamar o código JS e o módulo compilado (WASM).
- Código em C (dentre outras opções) compilado em WASM.
- Código JS que chama código em C (compilado em WASM).

## Compilar

- `emcc lib/demo.c -s WASM=1 -O3 -o public/demo.html` (gera página, código em JS e WASM)
- `emcc lib/demo.c -s WASM=1 -O3 -o public/demo.js` (exige que seja chamado por uma página HTML)
- `emcc lib/demo.c -s WASM=1 -O3 --pre-js antes.js -o demo.js`
- `emcc lib/demo.c -s WASM=1 -O3 --post-js apos.js -o demo.js`
- `emcc lib/demo.c -s WASM=1 -s EXPORTED_FUNCTIONS="['_numero', '_main']" -O3 --post-js apos.js -o public\demo.js` (JavaScript pode chamar as funções _\_numero()_ e _\_main()_)

## ccall (chamar código em C a partir de JavaScript)

- `ccall("quadrado", "number", ["number"], [9])` (faz chamada à função **quadrado**, que retorna um número e recebe outro número como argumento, neste caso, o valor 9, ou seja, o retorno esperado é 81.)

## Chamar código em JavaScript a partir de C

Não é o cenário típico de uso.

- Importe **emscripten.h**
- Use `emscripten_run_script("console.log('mensagem...')");`

- Usando chamada assíncrona
- Use `emscripten_async_run_script("console.log('mensagem...')", 2000);`

- Chamando função JavaScript que retorna um inteiro
- Use `int valorInt = emscripten_run_script_int("getNum()");`

## Alguns links

- [WebAssembly.instantiateStreaming()](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/WebAssembly/instantiateStreaming)

## WebAssembly a partir de código em C (básico)

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
