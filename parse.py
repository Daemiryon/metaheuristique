def parseFile(fileName):
    f = open(fileName)
    n = int(f.readline())

    input = []
    Ingredient = set()

    for i in range(n):
        likes = f.readline().strip().split(" ")
        dislikes = f.readline().strip().split(" ")
        out = {
            "likes":[],
            "dislikes":[],
        }

        Ingredient|=set()

        if likes[0] == "0": likes = []
        else :
            out["likes"] = likes[1:]
            Ingredient|=set(likes[1:])
        
        if dislikes[0] == "0":dislikes = []
        else:
            out["dislikes"] = dislikes[1:]
            Ingredient|=set(dislikes[1:])

        input.append(out)
    
    return input,list(Ingredient)

