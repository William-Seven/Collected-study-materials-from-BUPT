class Vehicle:
    # 类属性，所有实例共享
    class_attribute = "This is a vehicle class"

    def __init__(self, brand, model, year):
        # 对象属性，特定实例独有
        self.brand = brand
        self.model = model
        self.year = year
        self.mileage = 0  # 初始里程数为0

    # 对象方法，描述车辆
    def description(self):
        return f"This vehicle is a {self.year} {self.brand} {self.model} with {self.mileage} miles."

    # 类方法，用于显示类的相关信息
    @classmethod
    def show_class_info(cls):
        return f"Class Info: {cls.class_attribute}"

    # 静态方法，与具体实例无关
    @staticmethod
    def vehicle_sound():
        return "Vehicles can make sounds."

    # 对象方法，更新里程数
    def update_mileage(self, miles):
        if miles >= self.mileage:
            self.mileage = miles
        else:
            print("Mileage cannot be rolled back.")

# Car类继承Vehicle类


class Car(Vehicle):
    def __init__(self, brand, model, year, num_doors):
        # 调用父类的构造函数
        super().__init__(brand, model, year)
        self.num_doors = num_doors
        self.fuel_level = 100  # 初始燃油水平

    # 重写父类的description方法，实现多态
    def description(self):
        return f"This car is a {self.year} {self.brand} {self.model} with {self.num_doors} doors and {self.mileage} miles."

    # 对象方法，描述燃油状态
    def fuel_status(self):
        return f"The car has {self.fuel_level}% fuel remaining."

    # 对象方法，加油
    def refuel(self, amount):
        if 0 <= self.fuel_level + amount <= 100:
            self.fuel_level += amount
        else:
            print("Fuel level must be between 0 and 100.")

# Motorcycle类继承Vehicle类


class Motorcycle(Vehicle):
    def __init__(self, brand, model, year, engine_type):
        # 调用父类的构造函数
        super().__init__(brand, model, year)
        self.engine_type = engine_type
        self.helmet_on = False  # 初始未戴头盔

    # 重写父类的description方法，实现多态
    def description(self):
        return f"This motorcycle is a {self.year} {self.brand} {self.model} with a {self.engine_type} engine and {self.mileage} miles."

    # 对象方法，戴头盔
    def wear_helmet(self):
        self.helmet_on = True
        return "Helmet is on."

    # 对象方法，检查头盔状态
    def check_helmet(self):
        return "Helmet is on." if self.helmet_on else "Helmet is off."


if __name__ == '__main__':
    # 对象实例化
    car = Car("Toyota", "Camry", 2021, 4)
    motorcycle = Motorcycle("Yamaha", "MT-07", 2022, "parallel-twin")

    # 使用对象方法和多态
    print(car.description())  # 输出Car类的描述
    print(motorcycle.description())  # 输出Motorcycle类的描述

    # 更新车辆里程数
    car.update_mileage(5000)
    motorcycle.update_mileage(3000)
    print(car.description())  # 更新后的描述
    print(motorcycle.description())

    # 调用类方法，显示类的信息
    print(Vehicle.show_class_info())

    # 调用静态方法，演示车辆的声音
    print(Vehicle.vehicle_sound())

    # Car类的特有方法演示
    print(car.fuel_status())
    car.refuel(-10)  # 尝试减少燃油
    print(car.fuel_status())

    # Motorcycle类的特有方法演示
    print(motorcycle.check_helmet())
    print(motorcycle.wear_helmet())
    print(motorcycle.check_helmet())
