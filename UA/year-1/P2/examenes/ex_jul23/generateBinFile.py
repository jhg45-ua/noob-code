import struct

# Definir empleados de ejemplo
employees = [
    ("74552233Q", "John Doe", 45000, 2015),
    ("04636467G", "Jane Smith", 50000, 2010),
    ("12345678A", "Alice Johnson", 60000, 2018),
    ("87654321B", "Bob Brown", 35000, 2019),
    ("56789012C", "Charlie Black", 55000, 2021),
]

# Crear el archivo binario
with open("cmake-build-debug/employees.bin", "wb") as f:
    for emp in employees:
        dni = emp[0].encode('utf-8').ljust(10, b'\x00')
        name = emp[1].encode('utf-8').ljust(100, b'\x00')
        bruteSalary = emp[2]
        startedYear = emp[3]
        f.write(struct.pack('10s100siI', dni, name, bruteSalary, startedYear))