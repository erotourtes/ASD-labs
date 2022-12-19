

let s = '{'
for (let i = 0; i < 7; i++) {
  s+= "{";
  for (let j = 0; j < 7; j++) {
    s += Math.floor(Math.random() * 10) + ', ';
  }
  s+= '}\n';
}

console.log(s + "}");
