#ifndef FILA_H
#define FILA_H

#ifndef TAM
#define TAM 50
#endif

template <typename T>
struct Fila {
    T info[TAM];
        int comeco, fim;
        };

        template <typename T>
        void inicializarFila(Fila<T>& f) {
            f.comeco = 0;
                f.fim = -1;
                }

                template <typename T>
                bool filaVazia(Fila<T> f) {
                    return f.fim < f.comeco;
                    }

                    template <typename T>
                    bool filaCheia(Fila<T> f) {
                        return f.fim == TAM - 1;
                        }

                        template <typename T>
                        bool inserirFila(Fila<T>& f, T valor) {
                            if (filaCheia(f)) return false;
                                f.fim++;
                                    f.info[f.fim] = valor;
                                        return true;
                                        }

                                        template <typename T>
                                        bool retirarFila(Fila<T>& f, T& valor) {
                                            if (filaVazia(f)) return false;
                                                valor = f.info[f.comeco];
                                                    f.comeco++;
                                                        return true;
                                                        }

                                                        #endif
                                                        