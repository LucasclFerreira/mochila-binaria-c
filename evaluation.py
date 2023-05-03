import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# rotulos para o eixo X (na plotagem) dos 10 primeiros conjuntos de testes
# são strings que contém o tamanho do teste
rotulos_x_fn = ['10_269', '20_878', '4_20', '4_11', '10_60', '7_50', '23_10000']

# todos esse dados são referentes aos testes que estão no formato "fx_l-d_kp_xx_xxx" em que x é apenas um exemplo de onde ficaria um número
# os dados assegui são inventados apenas para testar a plotagem
# mas poderiam ser trocaos por valores reais para obtermos as imagens
dados_fn_prog_dinam = pd.Series([2, 6, 1, 0.5, 4, 3, 23], index=rotulos_x_fn, name='prog_dinam')
dados_fn_forca_bruta = pd.Series([13, 31, 4, 3, 26, 22, 120], index=rotulos_x_fn, name='forca_bruta')
dados_fn_alg_guloso = pd.Series([4, 12, 2, 1, 8, 7, 56], index=rotulos_x_fn, name='alg_guloso')

# o mesmo pode ser feito para os dados referentes aos teste que estão no formato "knapPI_1_xxxx_xxxx_1" e etc
dados_knapPI_1 = pd.Series(np.arange(0, 7), index=['100_1000', '200_1000', '500_1000', '1000_1000', '2000_1000', '5000_1000', '10000_1000'], name='fn')

tabela = pd.concat([dados_fn_prog_dinam, dados_fn_forca_bruta, dados_fn_alg_guloso], axis=1)
#tabela = pd.DataFrame(tabela)

print(dados_fn_prog_dinam)
print(dados_fn_forca_bruta)
print(dados_fn_alg_guloso)

print(tabela)

#tabela = pd.concat([dados_fn, dados_knapPI_1], axis=1)
fig, axes = plt.subplots()
tabela.plot.bar(ax=axes, color=['red', 'green', 'blue'])
plt.xticks(rotation=20)

plt.show()