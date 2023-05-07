import numpy as np
import pandas as pd
import plotly.graph_objects as go

# rotulos para o eixo X (na plotagem) dos 10 primeiros conjuntos de testes
# são strings que contém o tamanho do teste
rotulos_x_fn = ['10_269', '20_878', '4_20', '4_11', '15_375', '10_60', '7_50', '23_10000', '5_80', '20_879']

# todos esse dados são referentes aos testes que estão no formato "fx_l-d_kp_xx_xxx" em que x é apenas um exemplo de onde ficaria um número
# os dados assegui são inventados apenas para testar a plotagem
# mas poderiam ser trocaos por valores reais para obtermos as imagens
dados_fn_forca_bruta = pd.Series([0, 0, 27, 22, 0, 0, 2732, 0, 136, 0], index=rotulos_x_fn, name='forca_bruta')
dados_fn_prog_dinam = pd.Series([1, 2, 1, 1, 1, 2, 1, 3, 1, 1], index=rotulos_x_fn, name='programacao_dinamica')
dados_fn_alg_guloso = pd.Series([38, 118, 6, 3, 70, 28, 6, 109, 11, 70], index=rotulos_x_fn, name='algoritmo_guloso')

# o mesmo pode ser feito para os dados referentes aos teste que estão no formato "knapPI_1_xxxx_xxxx_1" e etc
#dados_knapPI_1_forca_bruta = pd.Series([0, 0, 27, 22, 0, 0, 2732, 0, 136, 0], index=rotulos_x_fn, name='forca_bruta')
dados_knapPI_1_prog_dinam = pd.Series([1, 1, 16, 48, 152, 1064, 0], index=rotulos_x_fn, name='programacao_dinamica')
dados_knapPI_1_alg_guloso = pd.Series([385, 1171, 6452, 28339, 113958, 723930, 0], index=rotulos_x_fn, name='algoritmo_guloso')

dados_knapPI_2_prog_dinam = pd.Series([1, 2, 9, 37, 145, 1059, 2969], index=rotulos_x_fn, name='programacao_dinamica')
dados_knapPI_2_alg_guloso = pd.Series([248, 580, 3714, 14824, 59253, 384967, 1474079], index=rotulos_x_fn, name='algoritmo_guloso')

dados_knapPI_3_prog_dinam = pd.Series([1, 3, 9, 35, 133, 1052, 4152], index=rotulos_x_fn, name='programacao_dinamica')
dados_knapPI_3_alg_guloso = pd.Series([26, 94, 356, 970, 3487, 20922, 94928], index=rotulos_x_fn, name='algoritmo_guloso')

tabela = pd.concat([dados_fn_prog_dinam, dados_fn_forca_bruta, dados_fn_alg_guloso], axis=1)
tabela = pd.DataFrame(tabela)

print(tabela)

fig = go.Figure(data=[go.Bar(name='Progração Dinâmica', x=tabela.index, y=tabela['programacao_dinamica']),
                      go.Bar(name='Força Bruta', x=tabela.index, y=tabela['forca_bruta']),
                      go.Bar(name='Algoritmo Guloso', x=tabela.index, y=tabela['algoritmo_guloso'])])

# update layout
fig.update_layout(title='Comparação entre os algoritmos',
                  xaxis_title='Conjunto de testes',
                  yaxis_title='Tempo de execução (milisegundos)')

fig.show()
