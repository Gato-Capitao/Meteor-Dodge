"""
This is a script that converts a specific sheet to arduino notes and syntax.

To do this just copy the text from the sheet and paste here, 
just be careful when putting spaces, 
it will convert to syntax and create a txt file with the name you gave, 
you can just copy the melody and paste using a specific structure in the code.



- Structure: https://www.tinkercad.com/things/5CR9DvAvyxt
- Example sheet: https://pianoletternotes.blogspot.com/2021/08/rush-e.html


Github: Gato-Capitao

Python 3.10.5
"""

#Configuracoes
limpar = False#Limpa os espaços entre as notas que algumas partituras possuem, como: F-3, resulta em: F3

#

def converter(nota:str, octave:str) -> str:
    """
    Converter de letra para a sintaxe do código
    """
    if(nota == "" or nota == "-"):
        return "0"
    texto = f"NOTE_{nota.upper()}"
    
    if(nota.lower() != nota):
        texto += "S"
    
    texto += octave
    
    return texto

def ajustarParte(partitura:list, limpar:bool = False) -> list:
    """
    Deixa a entrada na sintaxe do Arduino.
    
    Ele junta as linhas da partitura que acontecem no mesmo momento,
    já que não tem como tocar as 2 notas no mesmo tempo, ele apenas junta se  a primeira linha tiver o espaço vazio.
    
    Exemplo:
    f-f-f-f-A--
    B-A-c-d-a-e
    
    Resulta em:
    f-f-f-f-A-e
    
    Que é convertido para a sintaxe do Arduino
    """
    def limparPausas(suja:list) -> list:
        """
        Limpa as pausas entre as teclas.
        
        Exemplo:
        4|f-f-e-a-b
        
        Com a função:
        NOTE_F4, NOTE_F4, NOTE_E4, NOTE_A4, NOTE_B4
        
        Sem a função:
        NOTE_F4, 0, NOTE_F4, 0, NOTE_E4, 0, NOTE_A4, 0, NOTE_B4
        
        """
        resultado = []
        for linha in suja:
            limpa = []
            contador = 0
            
            while contador < len(linha):
                limpa.append(linha[contador])
                contador += 2
            
            resultado.append(limpa)
        
        return resultado
    
    lista = []
    #Converter a partitura para as palavras chaves do cod do Arduino
    for i in partitura:
        octave, notas = i.split("|")
        
        lista.append([converter(n, octave) for n in notas])
        
    #Limpar os espaços desnecessarios a cada nota
    if limpar:
        lista = limparPausas(lista)
    
    #Juntar as notas das mãos caso a parte esteja vazia
    definido = list(lista[0])
    for c in range(len(lista[0])):#Fazer isso para cada elemento da lista de notas
        if definido[c] == "0":
            for pos in range(len(lista)):#Fazer isso para cada elemento na lista das listas de notas
                if lista[pos][c] != "0":
                    definido[c] = lista[pos][c]
                    break
    
    return definido

#Ler nome da melodia
nome = input("Melody name(Do not use special characters): ")
print("Paste the melody and finish with EOF(Press Ctrl+Z)")


#Ler a partitura no prompt, separar os dados e armazena-los em listas
"""
Fica lendo o prompt até que aconteça EOF.

Quando a mão lida é diferente da última, ele fecha aquela parte,
Porque o mesmo momento pode usar mais de uma linha por mão.

"""
partitura = {
    "RH":[],
    "LH":[]
        }
parte = []
ultima = ""
while True:
    try:
        #Separar entrada em variaveis
        mao, resto = input().split(":")
        
        #Remover a última barra
        resto = resto[:-1]
        
        #Adicionar em parte caso seja repetida
        if(mao != ultima and ultima != "" and len(parte) > 0):
            linha = ajustarParte(parte, limpar)
            partitura[ultima].append(linha)
            parte = []
        
        parte.append(resto)
        
        ultima = mao
        

    except EOFError:
        if len(parte) > 0:
            linha = ajustarParte(parte, limpar)
            partitura[mao].append(linha)
        break


#Conveter as notas da partitura para um texto com a sintaxe do Arduino.
texto = ""
for mao, passo in partitura.items():
    texto += f'{mao}\n'+"{"
    
    for linha in passo:
        for n in linha:
            texto += f"{n}, "
        
        texto = texto[:-1]+"\n"
    
    texto = texto[:-2]+"}\n"


#Jogar tudo em um arquivo txt
with open(f"{nome}.txt", "w") as arquivo:
    arquivo.write(texto)

#Mostrar os dados no prompt
print(f"Nome: {nome}\nCodigo\n{texto}")
