# 🎅 Santa Claus Problem

Implementação do clássico **Santa Claus Problem** utilizando **threads**, **mutexes** e **variáveis de condição** para sincronização entre processos concorrentes.

## 📖 Sobre o Problema

O *Santa Claus Problem* é um problema clássico de sincronização proposto por Ian Dowse, amplamente utilizado para demonstrar conceitos de concorrência e comunicação entre threads.

O cenário envolve três tipos de participantes:

* 🎅 Papai Noel
* 🦌 9 Renas
* 🧝 10 Elfos

Cada participante executa suas atividades de forma independente, exigindo mecanismos de sincronização para garantir o cumprimento das regras do sistema.

---

## 🎯 Objetivo

Implementar uma solução concorrente que coordene corretamente a interação entre Papai Noel, renas e elfos, evitando condições de corrida (*race conditions*) e garantindo a correta sincronização das threads.

---

## 🧩 Funcionamento

### 🎅 Papai Noel

O Papai Noel permanece dormindo até que uma das seguintes condições ocorra:

1. Todas as 9 renas retornem das férias.
2. Um grupo de 3 elfos necessite de ajuda.

Ao ser acordado:

* Se as 9 renas estiverem presentes, ele prepara o trenó para a entrega dos presentes.
* Se houver um grupo de 3 elfos aguardando, ele responde às suas dúvidas antes de voltar a dormir.

---

### 🦌 Renas

Cada rena passa um período de férias e retorna ao Polo Norte posteriormente.

Quando todas as 9 renas retornam:

1. Elas acordam o Papai Noel.
2. Aguardam a preparação do trenó.
3. São liberadas para uma nova rodada de férias após a conclusão da entrega dos presentes.

---

### 🧝 Elfos

Os elfos trabalham continuamente na fabricação de brinquedos.

Quando um elfo encontra um problema:

1. Ele entra em uma fila de espera.
2. Apenas grupos de 3 elfos podem solicitar ajuda ao Papai Noel.
3. Após receberem ajuda, retornam ao trabalho.

---

## ⚠️ Regras de Sincronização

* O Papai Noel só pode ser acordado por:

  * Todas as 9 renas;
  * Um grupo de exatamente 3 elfos.

* Enquanto um grupo de elfos está sendo atendido, os demais devem aguardar.

* As renas possuem prioridade sobre os elfos quando todas as 9 retornam simultaneamente.

* Nenhum elfo pode receber ajuda individualmente.

* As renas só prosseguem após o Papai Noel concluir a preparação do trenó.

---

## 🔒 Mecanismos Utilizados

Para garantir a sincronização entre as threads, foram utilizados:

* **Mutexes**

  * Proteção de regiões críticas.
  * Controle de acesso às variáveis compartilhadas.

* **Variáveis de Condição (Condition Variables)**

  * Bloqueio e despertar de threads.
  * Coordenação entre Papai Noel, renas e elfos.

* **Threads**

  * Execução concorrente dos participantes do sistema.

---

## 📂 Estrutura do Projeto

```text
SantaClausProblem/
│
├── santa.c
├── santa.h
├── Makefile
└── README.md
```

---

## ⚙️ Compilação

```bash
gcc santa.c -o santa -lpthread
```

## ▶️ Execução

```bash
./santa
```

---

## 📚 Conceitos Aplicados

* Programação Concorrente
* Threads POSIX (Pthreads)
* Mutexes
* Variáveis de Condição
* Sincronização de Processos
* Exclusão Mútua
* Controle de Concorrência

---

## 👩‍💻 Autora

**Mikaela Rikberg Alves**

Projeto desenvolvido para estudos de Programação Concorrente e Sistemas Operacionais.


