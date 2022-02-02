#include <iostream> 

#include <datastore.hpp>

int main() {
    using namespace socksave;

    DataStore ds(30, "output/", "PREFIX");

    ds.write("ESSA É UMA STRING MUITO LONGA ");
    ds.write("QUE EU ESTOU ESCREVENDO PRA TESTAR O PROGRAMA ");
    ds.write("QUE POR SUA VEZ DEVE SALVAR ISSO EM MÚLTIPLOS ARQUIVOS ");
    ds.write("MAS APENAS SE NECESSÁRIO, NÃO VAMOS FAZER BOBAGEM ");

    // ds.write("A123456789");
    // ds.write("B123456789");
    // ds.write("C123456789");
    // ds.write("D123456789");
}