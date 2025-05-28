# Kroma Programming Language Specification

Kroma is a dynamic, artist-friendly, general-purpose language designed to facilitate creative coding, artistic prototyping, and interactive media systems. It blends expressiveness with minimal syntax and supports high-level constructs for generative and interactive work.

---

## 📦 Overview

- **Paradigm:** Imperative, Object-Oriented, Functional elements
- **Typing:** Dynamic (no explicit type annotations)
- **Execution:** Hybrid (interpreted for development, optionally compiled to WebAssembly or native binary)
- **Syntax Style:** Indentation-based blocks, influenced by Python and JavaScript
- **File Extension:** `.kro`
- **CLI Usage:** `kroma run archivo.kro`, `kroma build archivo.kro`, `kroma webbuild archivo.kro`

---

## 🗃 Reserved Words

```
let, const, def, class, if, else, for, while, loop, break, continue,
return, import, from, as, true, false, null, and, or, not
```

---

## 🔤 Variables

### Declaration

```kroma
let nombre = "Lora"
const PI = 3.1416
```

### Reassignment

```kroma
nombre = "Gifre"   # ✅
PI = 3.15          # ❌ Error: constant reassignment
```

---

## 🔁 Control Structures

### Conditional

```kroma
if temperatura > 30 {
  print("Hace calor")
} else {
  print("Está fresco")
}
```

### Loops

```kroma
loop {
  print("Bucle infinito")
}

for i in 0..10 {
  print(i)
}

while condicion {
  hacer_algo()
}
```

---

## 🔧 Functions

```kroma
def saludar(nombre) {
  print("Hola " + nombre)
}

saludar("Sigi")
```

---

## 🎨 Objects and Classes

```kroma
class Pincel {
  def init(color) {
    this.color = color
  }

  def trazar(x, y) {
    circle(x: x, y: y, radius: 5, color: this.color)
  }
}

let p = Pincel("red")
p.trazar(100, 100)
```

---

## 🎛 Built-in Types

- `texto` (strings)
- `número` (ints and floats)
- `bool` (`true`, `false`)
- `lista` (arrays)
- `mapa` (dictionaries)
- `objeto` (instances)
- `null`

---

## 🎨 Canvas API (standard module)

```kroma
canvas(width: 800, height: 600)

loop {
  clear()
  circle(x: 400, y: 300, radius: 100, color: "cyan")
}
```

---

## 🧠 Error Handling

```kroma
def dividir(a, b) {
  if b == 0 {
    fail("No se puede dividir por cero")
  }
  return a / b
}

let resultado = try(dividir(10, 0))

if is_error(resultado) {
  print("Error: " + resultado.message)
} else {
  print("Resultado: " + resultado)
}

panic("Error fatal")
```

---

## 🔌 Planned Native Modules

- `sound`
- `midi`
- `device`
- `web`
- `ml`
- `anim`

---

## 🔚 Summary

Kroma is designed to empower creative minds to build visually rich, interactive, and generative works with minimal syntax overhead and maximal expressive control.
