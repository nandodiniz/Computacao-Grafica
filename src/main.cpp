// gerar_estrutura.cpp
// Gera uma estrutura 3D (piramide em degraus com torre e pilares) e grava em modelo.json
// Compilar: g++ -std=c++17 -O2 gerar_estrutura.cpp -o gerar
// Executar: ./gerar   (cria/atualiza modelo.json na mesma pasta)

#include <cstdio>
#include <vector>

struct Malha {
    std::vector<float> pos;   // x,y,z por vertice
    std::vector<float> cor;   // r,g,b por vertice
    std::vector<int> idx;     // triangulos

    // Adiciona uma caixa centrada em (cx,cy,cz) com dimensoes (sx,sy,sz)
    void caixa(float cx, float cy, float cz, float sx, float sy, float sz,
               float r, float g, float b) {
        const float hx = sx / 2, hy = sy / 2, hz = sz / 2;
        // 6 faces, 4 vertices cada (vertices separados => sombreamento plano)
        const float faces[6][4][3] = {
            {{-1,-1, 1},{ 1,-1, 1},{ 1, 1, 1},{-1, 1, 1}}, // frente
            {{ 1,-1,-1},{-1,-1,-1},{-1, 1,-1},{ 1, 1,-1}}, // tras
            {{-1, 1, 1},{ 1, 1, 1},{ 1, 1,-1},{-1, 1,-1}}, // topo
            {{-1,-1,-1},{ 1,-1,-1},{ 1,-1, 1},{-1,-1, 1}}, // base
            {{ 1,-1, 1},{ 1,-1,-1},{ 1, 1,-1},{ 1, 1, 1}}, // direita
            {{-1,-1,-1},{-1,-1, 1},{-1, 1, 1},{-1, 1,-1}}  // esquerda
        };
        for (int f = 0; f < 6; ++f) {
            int base = (int)pos.size() / 3;
            for (int v = 0; v < 4; ++v) {
                pos.push_back(cx + faces[f][v][0] * hx);
                pos.push_back(cy + faces[f][v][1] * hy);
                pos.push_back(cz + faces[f][v][2] * hz);
                cor.push_back(r); cor.push_back(g); cor.push_back(b);
            }
            idx.insert(idx.end(), {base, base + 1, base + 2, base, base + 2, base + 3});
        }
    }

    void salvar(const char* arquivo) const {
        FILE* f = fopen(arquivo, "w");
        if (!f) { perror("erro ao abrir arquivo"); return; }
        auto escreveF = [&](const char* nome, const std::vector<float>& v) {
            fprintf(f, "  \"%s\": [", nome);
            for (size_t i = 0; i < v.size(); ++i) fprintf(f, "%s%.4f", i ? "," : "", v[i]);
            fprintf(f, "]");
        };
        fprintf(f, "{\n");
        escreveF("positions", pos); fprintf(f, ",\n");
        escreveF("colors", cor);    fprintf(f, ",\n");
        fprintf(f, "  \"indices\": [");
        for (size_t i = 0; i < idx.size(); ++i) fprintf(f, "%s%d", i ? "," : "", idx[i]);
        fprintf(f, "]\n}\n");
        fclose(f);
    }
};

int main() {
    Malha m;

    // Chao
    m.caixa(0, -0.1f, 0, 24, 0.2f, 24, 0.20f, 0.22f, 0.26f);

    // Piramide em degraus (6 niveis)
    const int niveis = 6;
    for (int i = 0; i < niveis; ++i) {
        float t = (float)i / (niveis - 1);
        float lado = 10.0f - i * 1.5f;
        float altura = 1.0f;
        float y = altura / 2 + i * altura;
        m.caixa(0, y, 0, lado, altura, lado, 0.9f - 0.5f * t, 0.45f + 0.35f * t, 0.25f + 0.65f * t);
    }

    // Torre central + ponta
    m.caixa(0, niveis + 1.5f, 0, 1.2f, 3.0f, 1.2f, 0.85f, 0.85f, 0.90f);
    m.caixa(0, niveis + 3.4f, 0, 0.5f, 0.8f, 0.5f, 1.0f, 0.25f, 0.25f);

    // Quatro pilares nos cantos
    const float p = 9.0f;
    const float cantos[4][2] = {{-p,-p},{p,-p},{p,p},{-p,p}};
    for (auto& c : cantos) {
        m.caixa(c[0], 2.0f, c[1], 1.2f, 4.0f, 1.2f, 0.75f, 0.70f, 0.55f);
        m.caixa(c[0], 4.3f, c[1], 1.6f, 0.6f, 1.6f, 0.95f, 0.85f, 0.40f);
    }

    m.salvar("modelo.json");
    printf("modelo.json gerado: %zu vertices, %zu triangulos\n", m.pos.size() / 3, m.idx.size() / 3);
    return 0;
}
