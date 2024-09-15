import plotly.express as px
from jinja2 import Template
import pandas as pd
import plotly.graph_objects as go
import os

output_html_path = r"../report.html"
input_template_path = r"./template.html"


def load_csv():
    pass

def main():
    # Create multiple figures
    fig1 = px.bar(px.data.gapminder().query("country == 'Canada'"),
                  x='year', y='pop', title="Population of Canada")
    fig2 = px.scatter(px.data.gapminder().query("country == 'United States'"),
                      x='year', y='gdpPercap', title="GDP Per Capita of United States")
    fig3 = px.line(px.data.gapminder().query("country == 'China'"),
                   x='year', y='lifeExp', title="Life Expectancy in China")

    # Convert figures to HTML
    plotly_jinja_data = {
        "fig1": fig1.to_html(full_html=False),
        "fig2": fig2.to_html(full_html=False),
        "fig3": fig3.to_html(full_html=False)
    }

    # Render template with multiple plots
    with open(output_html_path, "w", encoding="utf-8") as output_file:
        with open(input_template_path) as template_file:
            j2_template = Template(template_file.read())
            output_file.write(j2_template.render(plotly_jinja_data))

    return


if __name__ == '__main__':
    main()
