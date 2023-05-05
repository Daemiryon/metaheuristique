
def score(pizza, inputs):
    score = 0
    for p in inputs:
        works = True
        # Vérifie que la pizza a tout les éléments
        for j in pizza:
            if j in p["dislikes"]:
                works = False
                break
        # Vérifie que l'utilisateur a tout les éléments de la pizza
        for j in p["likes"]:
            if j not in pizza:
                works = False
                break
        if works:
            score += 1
    return score


def score2(pizza, inputs):
    score = 0
    for p in inputs:
        for j in pizza:
            if j in p["dislikes"]:
                score += 1
                break
    return score
