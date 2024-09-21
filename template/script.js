function calcularOcupacao() {
  // Obtendo os valores dos inputs
  const taxaEntrada = parseFloat(document.getElementById('entrada').value)
  const taxaAtendimento = parseFloat(
    document.getElementById('atendimento').value
  )
  // Verificando se todos os valores foram inseridos
  if (isNaN(taxaEntrada) || isNaN(taxaAtendimento)) {
    document.getElementById('resultado').innerText = ' = Not valid!'
    return
  }

  // Calculando a ocupação (taxa de atendimento / taxa de entrada)
  const ocupacaoCalculada = ((taxaAtendimento / taxaEntrada) * 100).toFixed(2)

  // Exibindo o resultado na página
  document.getElementById('resultado').innerText = ` = ${ocupacaoCalculada}%`
}
