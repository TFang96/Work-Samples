

function QuadraticFormula() {
  var a = document.querySelector('#a').value;
  var b = document.querySelector('#b').value;
  var c = document.querySelector('#c').value;
  let numerator = -b + Math.sqrt(Math.pow(b, 2) - 4*a*c);
  let denominator = 2*a;
  let result1 = numerator/denominator;
  
  numerator = -b - Math.sqrt(Math.pow(b, 2) - 4*a*c);
  let result2 = numerator/denominator;
  
  return [result1, result2];
}

function DisplayResults() {
  document.getElementById('answer').innerHTML = "Result: " + QuadraticFormula()[0] + ", " + QuadraticFormula()[1];
}