import plotly.express as px
from jinja2 import Template
import pandas as pd
import plotly.graph_objects as go
import os

output_html_path = r"../report.html"
input_template_path = r"./template.html"
csv_path = r"../c_project/data/"


def load_csv():
    arquivos_csv = [f for f in os.listdir(csv_path) if f.endswith('.csv')]
    dataframes = []
    for arquivo in arquivos_csv:
        caminho_arquivo = os.path.join(csv_path, arquivo)
        df = pd.read_csv(caminho_arquivo)
        if not df.empty:
            number = arquivo.split('output')[-1].split('.')[0]
            params = f"(E:{df.iloc[0]['Chegada']}, S:{df.iloc[0]['Saida']})"
            df['Fonte'] = f'{number}% - {params}'
        dataframes.append(df)

    df_combined = pd.concat(dataframes, ignore_index=True)
    return df_combined


def render_to_html(figs):
    # Convert figures to HTML
    plotly_jinja_data = {
        "fig1": figs[0].to_html(full_html=False, include_plotlyjs='cdn'),
        "fig2": figs[1].to_html(full_html=False, include_plotlyjs='cdn'),
        "fig3": figs[2].to_html(full_html=False, include_plotlyjs='cdn'),
        "fig4": figs[3].to_html(full_html=False, include_plotlyjs='cdn'),
        "fig5": figs[4].to_html(full_html=False, include_plotlyjs='cdn')
    }

    # Render template with multiple plots
    with open(output_html_path, "w", encoding="utf-8") as output_file:
        with open(input_template_path) as template_file:
            j2_template = Template(template_file.read())
            output_file.write(j2_template.render(plotly_jinja_data))


def main():
    df = load_csv()
    figs = []

    fig = px.line(df, x='Time', y="Ocupacao",
                  color='Fonte', title='Utilização (Ocupação)')
    figs.append(fig)

    fig = fig = px.line(df, x='Time', y="Fila Max",
                        color='Fonte', title='Máximo de Fila')
    figs.append(fig)

    fig = fig = px.line(df, x='Time', y=[
                        "E[N]", "E[W]"], color='Fonte', title='Média de elementos no sistema')
    figs.append(fig)

    fig = px.line(df, x='Time', y="Lambda", color='Fonte')
    figs.append(fig)

    fig = px.line(df, x='Time', y="Erro de Little",
                  color='Fonte', title='Erro de little')
    figs.append(fig)

    render_to_html(figs)

    return


if __name__ == '__main__':
    main()
