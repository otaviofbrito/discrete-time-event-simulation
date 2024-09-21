function calcularOcupacao() {
  // Obtendo os valores dos inputs
  const taxaEntrada = parseFloat(document.getElementById('util_lambda').value)
  const taxaAtendimento = parseFloat(document.getElementById('util_mu').value)
  // Verificando se todos os valores foram inseridos
  if (isNaN(taxaEntrada) || isNaN(taxaAtendimento)) {
    document.getElementById('util_res').innerText = ' = Not valid!'
    return
  }

  // Calculando a ocupação (taxa de atendimento / taxa de entrada)
  const ocupacaoCalculada = ((taxaAtendimento / taxaEntrada) * 100).toFixed(2)

  // Exibindo o resultado na página
  document.getElementById('util_res').innerText = ` = ${ocupacaoCalculada}%`
}

function calcularL() {
  const rho = parseFloat(document.getElementById('e_rho').value)
  if (isNaN(rho)) {
    document.getElementById('e_res').innerText = ' = Not valid!'
    return
  }
  const e_n = (rho / (1 - rho)).toFixed(2)
  document.getElementById('e_res').innerText = ` = ${e_n}`
}
