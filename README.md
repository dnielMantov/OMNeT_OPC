# OMNeT++ e OPC UA
O seguinte repositório versiona códigos experimentais desenvolvidos durante a pesquisa de simulação entre OPC UA e OMNeT++ realizada no Laboratório de Instrumentação Eletrônica e Controle (LIEC) da Universidade Federal de Campina Grande (UFCG).

Foram utilizados o framework OPC UA em C++ da Unified Automation e o framework INET para OMNeT++.

Para mais informações do funcionamento do código, integração do SDK da Unified Automation com o OMNeT++, build e execução, consulte a **documentação** fornecida no arquivo "Manual de Integração e Simulação OMNeT++ com OPC UA.pdf" na raiz do projeto.

As etapas foram registradas em branches distintas, consulte-as a seguir.

## Branches:
- master: código da primeira simulação demonstrada na documentação.
- randomUpdates: simulação entre 5 clientes e 1 servidor com atualizações randômicas de nós.
- INET: simulação de conexão entre 2 hosts com um switch intermediário utilizando o framework INET.

A cada mudança de branch (tendo em vista que todos os passos para a configuração de ambiente na documentação anexada foram seguidos) é necessário realizar uma build, para executar o programa, acesse a pasta `simulations` e execute o script `run_simulation`

    ./run_simulation
