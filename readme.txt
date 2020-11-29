Utilizar o mesmo teste do p3, executando: make APPLICATION=hello_p3 run

- Será printado a inicialização dos 4 cores
- Alem do teste de escalonamento com o escalonador FS com filas globais (MCFS).
- O escalonador funciona como o implementado para single-core, porem, cada core seleciona de uma fila global a thread que 
irá executar. Por sua vez, cada core fica responsável pela execução da thread até sua finalização
- No final de cada impressão da execução da thread adicionamos o número do core que executou (no formato <CORE_NUMBER> do preembulo), desta forma é possível ver que uma mesma thread sempre utiliza o mesmo processador.
