/**
 * Servidor de páginas estático.
 */

const express = require("express");
const app = express();

app.use(express.static("public"));

app.listen(2222, () => console.log("Server escutando na porta 2222"));
