Compilando:
executar: make APPLICATION=hello run
- Será impresso a sequências de prints que demonstram o funcionamento do escalonador.

Validações:
executar: make APPLICATION=hello debug
Para os pontos seguintes optamos por exemplificar com debug pois nao conseguimos acessar valores inline de registradores e de alguns
locais da memoria especifico no espaco de usuario.

Validaçao da inicializacao:
  - Breakpoint rv32_crt0.S:29, x &_bss_start ou verificar que uma variavel global que printamos esta setada com valor 0.
  - rv32_crt0.s:33 mtvec iniciado modo 0 com endereco da label _int_entry
  - rv32_crt0.s:15 satp iniciado com zero
  - rv32_crt0.s:39 será possivel perceber a configuracao de satp, mtvec, bss, sp
  - não há configuracao da cache.

Validacao da UART e Escalonador:
  - Durante a execuçao, irá printar qual thread terminou antes e depois. 

Switch context:
- Adicionar breakpoits no inicio e fim da função
- Executar o comando `info registers`:
  - Validar que os valores impressos para os registradores estão de acordo com a troca de contexto.
  - Houve a mudanca do valor dos registradores, principalmente, sp
