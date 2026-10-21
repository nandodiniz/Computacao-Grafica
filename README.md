# Computação Gráfica

Aplicação desenvolvida para a disciplina de Computação Gráfica. O objetivo é
renderizar cenas 3D em tempo real com shaders programáveis, aplicando
transformações geométricas, câmera interativa, iluminação e texturização.

## Funcionalidades previstas

- Renderização de cenas e objetos tridimensionais em tempo real.
- Transformações geométricas, como translação, rotação e escala.
- Câmera interativa para navegação pela cena.
- Iluminação calculada por shaders.
- Aplicação de texturas aos objetos.

## Tecnologias

- C e/ou C++.
- Shaders programáveis (GLSL, caso seja adotado OpenGL).
- A biblioteca gráfica e as dependências de compilação serão definidas durante
  o desenvolvimento.

## Estrutura do repositório

```text
.
├── src/
│   └── main.cpp
└── README.md
```

## Compilar a base C++

Com um compilador C++ disponível no terminal, como o `g++`:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic src/main.cpp -o Computacao-Grafica.exe
.\Computacao-Grafica.exe
```

O Go Live serve páginas web e não compila nem executa este programa C++ nativo.
Para visualizar a cena no navegador, será necessário preparar depois uma versão
web, por exemplo com WebAssembly, ou uma página de visualização separada.

## Estado do projeto

Este repositório está sendo preparado para o desenvolvimento do trabalho. As
funcionalidades e instruções de compilação serão atualizadas conforme a
implementação e a escolha das dependências.
