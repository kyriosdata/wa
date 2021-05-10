## Iniciar

1. Obténha dependências (Express) `yarn install`
1. Compile o código em C para WASM
   `emcc lib/canvas.c -s WASM=1 -s EXPORTED_FUNCTIONS="['_iniciar','_obterTamanho','_obterTotalItens','_atualizaPosicoes']" -o public/canvas.js`
1. Iniciar servidor (Express) para disponibilizar a aplicação web contida no diretório `public`
   na porta 2222 (localhost).
   `yarn run start`
