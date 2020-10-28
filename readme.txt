Compilando:
executar: make APPLICATION=hello run
- Será impresso a sequências de prints que demonstram o funcionamento do escalonador.

executar: make APPLICATION=hello debug
Para os pontos seguintes optamos por exemplificar com debug pois nao conseguimos acessar valores inline de registradores e de alguns
locais da memoria especifico no espaco de usuario.

Switch context:
- Adicionar breakpoits no inicio e fim da função
- Executar o comando `info registers`:
  - Validar que os valores impressos para os registradores estão de acordo com a troca de contexto.
