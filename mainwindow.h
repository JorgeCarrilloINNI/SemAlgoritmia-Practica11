#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<iostream>
#include<list>
#include <QPlainTextEdit>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Neurona{
private:
    int id;
    float voltaje;
    int posicion_x;
    int posicion_y;
    int red;
    int blue;
    int green;
    list<Neurona*> aristas;
    bool visitado;
public:
    Neurona(): visitado(false){};
    Neurona(int I, float V, int PX, int PY, int R, int G, int B): id(I), voltaje(V), posicion_x(PX), posicion_y(PY), red(R), green(G), blue(B){
          };
    void print(){
        cout<<"Neurona: "<<id<<endl;
        cout<<"voltaje: "<<voltaje<<endl;
        cout<<"posicion_x: "<<posicion_x<<endl;
        cout<<"posicion_y: "<<posicion_y<<endl;
        cout<<"red: "<<red<<" blue: "<<blue<<" green: "<<green<<endl;
    };
    int getId(){return id;}
    float getVoltaje(){return voltaje;}
    int getPosX(){return posicion_x;}
    int getPosY(){return posicion_y;}
    int getRed(){return red;}
    int getBlue(){return blue;}
    int getGreen(){return green;}

    void agregar_arista(Neurona* n) { aristas.push_back(n); }
    const list<Neurona*>& getAristas() const { return aristas; }

    void marcarVisitado(bool estado){
        visitado = estado;
    }
    bool esVisitado(){
        return visitado;
    }
};

class admNeurona{
private:
    list<Neurona> listaNeuronas;
public:
    void imprimirListaAdyacencia(QPlainTextEdit* plainTextEdit, Neurona& nodo) {
        for (Neurona* vecino : nodo.getAristas()) {
            plainTextEdit->appendPlainText("\t- Nodo " + QString::number(vecino->getId()));
            cout<<"\t -Nodo "<<vecino->getId()<<endl;
        }

        plainTextEdit->appendPlainText("");
    }
    void busquedaProfundidadAux(Neurona& nodo, QPlainTextEdit* plainTextEdit) {
        nodo.marcarVisitado(true);
        plainTextEdit->appendPlainText("Visitando nodo: " + QString::number(nodo.getId()));
        cout<<"Visitando nodo: "<<nodo.getId()<<endl;
        imprimirListaAdyacencia(plainTextEdit, nodo);

        for (Neurona* vecino : nodo.getAristas()) {
            if (!vecino->esVisitado()) {
                busquedaProfundidadAux(*vecino, plainTextEdit);
            }
        }
    }
    void busquedaProfundidad(Neurona& nodo, QPlainTextEdit* plainTextEdit) {
        for (Neurona& n : listaNeuronas) {
            n.marcarVisitado(false);
        }
        busquedaProfundidadAux(nodo, plainTextEdit);
    }
    void agregar_inicio(Neurona neurona){
        listaNeuronas.insert(listaNeuronas.begin(), neurona);
    }    
    void agregar_final(Neurona neurona){
        listaNeuronas.push_back(neurona);
    }

    void mostrar(){
        for(Neurona neurona : listaNeuronas){
            cout<<"--------------"<<endl;
            neurona.print();
            cout<<"--------------"<<endl;
        }
    }
    list<Neurona>& listaNeurona(){
        return listaNeuronas;
    }
    list<Neurona>& listaClear(){
        listaNeuronas.clear();
        return listaNeuronas;
    }


};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void crearNeuronaInicio();
    void crearNeuronaFinal();
    void mostrar();

private slots:
    void on_openFile_triggered();
    void on_actionRecuperar_triggered();
    void on_actionID_triggered();
    void on_actionVoltaje_triggered();

    void on_MostraTabla_clicked();

    void on_BuscarID_clicked();

    void on_graficarNeurona_clicked();

    void on_mostrarPuntos_clicked();

    void on_enlazar_clicked();

    void on_graficarGrafos_clicked();

    void on_profundidad_clicked();

private:
    Ui::MainWindow *ui;
    admNeurona listaNeuronas;
};

#endif // MAINWINDOW_H
