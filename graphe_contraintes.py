# Génère un graphe de contraintes des clients avec plantUML
import argparse
import os
from parse import parseFile


# fonction principale
def generate_graph(data_file, graph_file) :

    tastes, ingredients = parseFile(data_file)

    graph = []

    for client_index in range(len(tastes)) :

        valid_clients = [k for k in range(client_index, len(tastes))]

        for ingr in tastes[client_index]["likes"] :
            dislikes = find_who_dislikes(ingr, tastes, valid_clients)
            for c in dislikes :
                #print("Client", client_index, "likes", ingr, "but", c, "dislikes it")
                graph += [(client_index, c)]
                valid_clients.remove(c)

        for ingr in tastes[client_index]["dislikes"] :
            likes = find_who_likes(ingr, tastes, valid_clients)
            for c in likes :
                #print("Client", client_index, "dislikes", ingr, "but client", c, "likes it")
                graph += [(client_index, c)]
                valid_clients.remove(c)

    uml_string = graph_to_uml(graph, len(tastes)) 
    print_in_file(uml_string, graph_file)




def find_who_dislikes(ingr_name, tastes, valid_index) :

    dislikes = []

    for client_index in valid_index :
        if ingr_name in tastes[client_index]["dislikes"] :
            dislikes += [client_index]

    return dislikes

def find_who_likes(ingr_name, tastes, valid_index) :

    likes = []

    for client_index in valid_index :
        if ingr_name in tastes[client_index]["likes"] :
            likes += [client_index]

    return likes


def graph_to_uml(graph, nb_clients) :

    noeuds = ""
    arretes = ""

    for c in range(nb_clients) :
        noeuds += "card " + str(c) + "\n"

    for arrete in graph :
        arretes += str(arrete[0]) + " -- " + str(arrete[1]) + "\n"

    uml = "@startuml\n"
    uml += "\n"
    uml += noeuds
    uml += "\n"
    uml += arretes
    uml += "\n"
    uml += "@enduml\n"

    return uml

def print_in_file(string, file_name) :
    myfile = open(os.path.dirname(os.path.abspath(__file__)) + "\\" + file_name, "w+")
    myfile.write(string)
    myfile.close()


# Parser arguments

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-d", "--datafile", type=str, default="Data/a_exemple.txt", help="Name of the file with clients' likes and dislikes")
    parser.add_argument("-g", "--graphfile", type=str, default="graph.puml", help="Name of the PlantUML graph file")
    args = parser.parse_args()

    generate_graph(args.datafile, args.graphfile)



