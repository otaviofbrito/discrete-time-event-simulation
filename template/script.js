function calcularOcupacao() {
  // Obtendo os valores dos inputs
  const taxaEntrada = parseFloat(document.getElementById('util_lambda').value)
  const taxaAtendimento = parseFloat(document.getElementById('util_mu').value)
  // Verificando se todos os valores foram inseridos
  if (isNaN(taxaEntrada) || isNaN(taxaAtendimento)) {
    document.getElementById('util_res').innerText = ' = Inválido!'
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
    document.getElementById('e_res').innerText = ' = Inválido!'
    return
  }
  const e_n = (rho / (1 - rho)).toFixed(2)
  document.getElementById('e_res').innerText = ` = ${e_n}`
}

function calcularW() {
  const mu = parseFloat(document.getElementById('e_mu').value)
  const lambda = parseFloat(document.getElementById('e_lambda').value)

  if (isNaN(mu) || isNaN(lambda)) {
    document.getElementById('w_res').innerText = ' = Inválido!'
    return
  }
  const e_w = (1 / (mu - lambda)).toFixed(2)
  document.getElementById('w_res').innerText = ` = ${e_w}`
}
