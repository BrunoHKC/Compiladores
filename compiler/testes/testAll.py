import os
from filecmp import cmp


testDirs = [x[0] for x in os.walk("./testes/")]
testDirs.pop(0)

fail = False

for d in testDirs:
	inputFile = './compilador '+d+'/input.pas'
	outputFile = d+'/output'
	os.system('echo "" > MEPA')
	os.system('./compilador '+d+'/input.pas > analisadorSintatico')
	if not cmp('./MEPA',outputFile,False):
		print('Falhou no teste '+d)
		fail = True 
		break
		
if not fail:
	print('Passou em todos os testes')
