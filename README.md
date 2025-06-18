# Estimativa de π com o Método de Monte Carlo usando pthreads (C)

## 🎯 Objetivo do Repositório

Este projeto tem como objetivo implementar o cálculo de π (Pi) utilizando o **método de Monte Carlo**, nas versões **sequencial** e **paralela** (usando a biblioteca `pthread.h`).

O projeto foi desenvolvido como parte da disciplina de **Computação de Alto Desempenho** da **Universidade do Vale do Rio dos Sinos (UNISINOS)**.

---

## 📌 Breve explicação do Método de Monte Carlo

O método de Monte Carlo é uma técnica probabilística utilizada para resolver problemas matemáticos através da geração de números aleatórios.

Neste caso, o cálculo de π é baseado na razão entre a área de um **quarto de círculo de raio 1** e um **quadrado de lado 1**, utilizando a seguinte fórmula:

\[
\pi \approx 4 \times \left( \frac{\text{Nº de pontos dentro do círculo}}{\text{Nº total de pontos gerados}} \right)
\]

O algoritmo consiste em:

1. Gerar um grande número de pontos aleatórios dentro de um quadrado.
2. Verificar quantos desses pontos caem dentro do círculo.
3. Aplicar a fórmula acima para obter a estimativa de π.

---

## 🖥️ Ambiente de Testes

Todos os testes de desempenho foram realizados em um ambiente **virtualizado** utilizando o **VirtualBox**, rodando o sistema **Kali Linux (amd64)**.

### Configuração da máquina virtual (VM)

- **Sistema Operacional:** Kali Linux (amd64)
- **CPUs alocadas:** 24 CPUs virtuais
- **Memória RAM alocada:** 107.284 MB (~104,8 GB)

### Configuração da máquina host (processador físico)

- **Modelo de CPU:** Intel com arquitetura híbrida (Performance e Efficient cores)
- **Número de núcleos físicos:** 24 núcleos (8 Performance-cores + 16 Efficient-cores)
- **Total de threads:** 32
- **Frequência Turbo Máxima:** Até 5.80 GHz  
*(Especificações detalhadas estão ilustradas na imagem abaixo)*

---

## 📂 Estrutura do Repositório

MonteCarlo_PI/

- pi.c --> Programa sequencial
- pi_thread --> Programa em paralelo

- resultados --> Pasta com os resultados de execução (prints de saída)

  - 1.000.000.000 --> Resultados com 1 Bilhão de pontos
  - 10.000.000.000 --> Resultados com 10 Bilhões de pontos
- executaveis --> Arquivos .exe gerados (compilados), separados por quantidade de pontos
  - 1.000.000.000 --> Resultados com 1 Bilhão de pontos
  - 10.000.000.000 --> Resultados com 10 Bilhões de pontos
- README.md --> Este arquivo

---

## ⚙️ Compilação e Execução

### ✅ Compilando os códigos

#### Versão Sequencial

```bash
gcc -o pi.exe pi.c 
```

#### Versão Paralela:

```bash
gcc -o pi_thread.exe pi_thread.c -lpthread
```

### ✅ Executando os programas

#### Versão Sequencial

```bash
./pi.exe
```

#### Versão Paralela

```bash
./pi_thread.exe
```

---

## 📝 Como alterar a quantidade de pontos e de threads

### ✅ Alterando o número de pontos a serem gerados (precisão do cálculo)

Em ambos os códigos (sequencial e paralelo), o número total de pontos está definido em uma constante, geralmente chamada:

``` c
#define NUM_PONTOS 1000000000  // Exemplo: 1 bilhão de pontos
```

Se quiser mudar, basta alterar o valor dessa constante para o número desejado. Exemplo:

``` c
#define NUM_PONTOS 10000000000  // Agora com 10 bilhões de pontos
```

Depois de alterar, recompile o código.

### ✅ Alterando o número de threads (apenas no código paralelo)

No código com pthreads, o número de threads também está definido por uma constante:

``` c
#define NUM_THREADS 4  // Exemplo: 4 threads
```

Se quiser testar com outra quantidade (exemplo: 8, 16, 32 threads), é só alterar o valor:

``` c
#define NUM_THREADS 16  // Agora com 16 threads
```

Depois de alterar, recompile o código.

### ✅ Resumo

| Modificação          | Onde alterar                                           | Precisa recompilar? |
| -------------------- | ------------------------------------------------------ | ------------------- |
| Quantidade de pontos | Valor da constante `NUM_PONTOS`                        | ✅ Sim               |
| Número de threads    | Valor da constante `NUM_THREADS` (somente no paralelo) | ✅ Sim               |


## 📊 Análise Detalhada dos Resultados

Para cada configuração de número de threads (1, 2, 4, 8, 16 e 32 threads), foram realizadas **8 execuções separadas**, tanto com **1 bilhão de pontos (10⁹)** quanto com **10 bilhões de pontos (10¹⁰)**.

Isso permitiu obter uma média mais confiável dos tempos de execução, reduzindo o impacto de variações naturais de desempenho causadas por processos de sistema, overhead de virtualização e limitações do hardware.

---

### 📌 Tempos Médios Obtidos (em segundos)

#### ✅ 1 Bilhão de Pontos

| Nº de Threads | Média de Tempo (s) |
|---|---|
| 1 | 27,23 |
| 2 | 11,61 |
| 4 | 14,97 |
| 8 | 39,34 |
| 16 | 46,10 |
| 32 | 49,49 |

---

#### ✅ 10 Bilhões de Pontos

| Nº de Threads | Média de Tempo (s) |
|---|---|
| 1 | 267,56 |
| 2 | 117,58 |
| 4 | 132,10 |
| 8 | 168,04 |
| 16 | 244,14 |
| 32 | 393,79 |

---

### 📌 Observações Principais

- **Ganho de desempenho significativo ao passar de 1 para 2 threads**, com speedups superiores a 2x.
- **A partir de 4 threads**, a eficiência diminuiu consideravelmente, indicando que o programa passou a sofrer com overhead de sincronização (causado principalmente pelo uso de mutex) e limitações da máquina virtual.
- Os **tempos de execução começaram a piorar com 8 threads ou mais**, mostrando claramente os efeitos negativos de:
  - Contenção no acesso ao mutex.
  - Overhead da criação e sincronização de muitas threads.
  - Limitações de performance típicas de ambientes virtualizados.

---

### 📌 Influência do Ambiente de Testes

> É importante destacar que **todos os testes foram executados em um ambiente virtualizado (VirtualBox)**, rodando o sistema **Kali Linux (amd64)**, com **24 CPUs virtuais alocadas** e **107.284 MB (~104,8 GB) de memória**.

Além disso, a máquina física (host) utilizada para as execuções possui o seguinte processador:

- **Modelo de CPU Host:** Intel Core i9-13900K (24 núcleos físicos: 8 Performance-cores + 16 Efficient-cores / Total de 32 threads).
- **Frequência Turbo Máxima:** Até 5.80 GHz.

Essa virtualização certamente introduziu um overhead adicional e influenciou os resultados de escalabilidade.

---

### 📌 Conclusão

Apesar das limitações de ambiente, o projeto demonstrou:

✅ Ganhos reais de desempenho para até 2 threads.  
✅ Impacto prático de problemas como **contenção de mutex** e **overhead de virtualização**.  
✅ Importância de ajustar o número de threads de acordo com a arquitetura e ambiente de execução.

Essa análise contribuiu para o entendimento prático dos conceitos de **paralelismo, sincronização e escalabilidade**.

## 📌 Observação Final

Esse repositório é para fins acadêmicos e pode ser adaptado ou otimizado em implementações futuras (exemplo: uso de técnicas de redução ou migração para bibliotecas como OpenMP ou MPI).
