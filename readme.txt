Executar : make APPLICATION=hello run

- Será mostrado em tela os testes de interrupção e timer.
Foram feitos com base no arquivo de teste tests/alarm_test/alarm_test.cc

- Será mostrado na tela também o teste do escalonador FS (Feedback Scheduler)  que simula múltiplas filas.
- Será mostrado que a thread 3 (fast_long_job) estaria passando por todas as filas. 
  Como comportamento esperado, ela deveria disputar a CPU logo no início e rodar algumas vezes até ser preemptada. 
  Após a finalização da thread 1 (fast_job), pois esta necessita de menos tempo para terminar todo seu trabalho, as threads 2 (slow_job) e 3 disputariam a CPU e
  o esperado seria uma alternância das threads o que realocaria ambas para a fila de menor prioridade. Por fim, a thread 3 deveria terminar sua execução por ultimo,
  pois o tempo necessário para terminar sua execução é muito alto, devido a quantidade de repetições do laço mais externo (que serve para printar uma mensagem que
  dá uma efeito cosmético a execução das threads).
	A preempção se mostra funcional, visto que o busy waiting das threads é pausado, dando lugar a outra thread. Além disso, foram feitos testes internos com laços
  infinitos e o mesmo resultado  (preempção) foi atingido. 
	O escalonador também se mostra funcional, pois atingiu os resultados esperados. Também, fizemos testes internos para comparar os resultados obtidos pelo 
  escalonador FS com o escalonador FCFS e mais uma vez, ambos tem resultados esperados.

	* O escalonador escolhido para a implementação foi o Feedback Scheduling. Nessa versão, foram implementadas 3 filas de prioridades, onde os jobs que executam 
  por tempo excessivo são rebaixados para a próxima fila de menor prioridade. O tempo excessivo está relacionado a sua preempção. Quando um job é preemptado 
  sem ter terminado sua tarefa (ocupa todo o quantum de tempo), em nossa implementação, ele é imediatamente realocado. Para testar o escalonador e a preempção, 
  foram criadas 3 funções que consomem CPU por meio de busy waiting (implementado com um laço longo). 

	* Existe um comportamento não-determinístico na execução do escalonador. Deduzimos que seja na preempção. Percebemos
  que mstatus.MIE não recebe mstatus.MPIE no fim da troca de contexto pois não chama mret. Forçamos este comportamento, e a nossa suspeita é que durante
  a habilitação de mstatus.MIE alguma interrupção (mip) pendente seja tratada antes de chegar em jalr.
	Por fim, o teste do Alarm foi feito no mesmo arquivo (hello.cc) usando um código similar ao código de teste de alarme do EPOS (alarm_test.cc).
