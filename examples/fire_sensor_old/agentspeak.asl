// Monitoramento e Alerta em uma Rede de Sensores
!start.

// Condições iniciais
+!start : true <-
    .my_name("sensor1");
    -sensor1;
   // -sensor2;
    //-sensor3;
    print_init.
    

// Reação ao ambiente e sociabilidade
+fire : true <- print_fire; +alert; .broadcast(tell,sensor1).
-fire : true <- print_not_fire; .broadcast(untell,sensor1).

