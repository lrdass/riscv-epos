Executar : make APPLICATION=hello_p3 run

- Será printado a inicialização dos 4 cores
- Alem do teste de escalonamento com o escalonador FS com filas globais (MCFS).
- O escalonador funciona como o implementado para single-core, porem, cada core seleciona de uma fila global a thread que 
irá executar. Por sua vez, cada core fica responsável pela execução da thread até sua finalização

make APPLICATION= hello run
- finc ja é implicitamente testado nas barreiras
- O hello irá executar o teste de operaçoes atomicas (rv32_cpu_test) (fdec, cas )

- IPI é implicitamente testado pois os 4 cores são inicializados.


- Será mostrado na tela também o teste do escalonador FS (Feedback Scheduler)  que simula múltiplas filas.
- Onde cada core pega do escalonador com filas globais.

* Existe um comportamento não-deterministico na inicialização dos cores, e durante a execução do tsl.