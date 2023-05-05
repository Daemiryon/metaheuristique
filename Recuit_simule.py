from parse import parseFile
from scoring import score, score2
import sys
import random as rd
from math import exp

filename = sys.argv[-1]
In, ingredients = parseFile(filename)

T = 2000.0
NB_accept = 0
Nb_ingredient = len(ingredients)

pizza0 = [rd.random() > 0.5 for _ in range(Nb_ingredient)]
score0 = -score([ingredients[i]for i in range(Nb_ingredient) if pizza0[i]], In)


def get_pizza_voisine(p):
    pv = p[:]
    i = rd.randint(0, Nb_ingredient)
    while i < Nb_ingredient:
        pv[i] = not (p[i])
        i += rd.randint(0, Nb_ingredient)
    return pv


def Metropolis_accept(DE):
    return (DE <= 0) or (rd.random() < exp(-DE/T))


while T > 0.0001:
    for i in range(100):
        pizza_voisine = get_pizza_voisine(pizza0)
        score_voisine = -score([ingredients[i] for i in range(
            Nb_ingredient) if pizza_voisine[i]], In)

        DE = score_voisine - score0

        if Metropolis_accept(DE):
            pizza0 = pizza_voisine
            score0 = score_voisine
            NB_accept += 1

        if NB_accept == 12:  # équilibre thermodynamique
            break

    NB_accept = 0
    print("Score : ", score0)
    T = 0.9*T
