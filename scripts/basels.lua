print('= YourClass =',YourClass)
for n,v in YourClass do print(n,v) end

b = YourClass.create('bill', 99, 34,65)
f = YourClass.create('fish', 44, 16.7,19.25)

local member_names = {'id','name','age','x','y'}

function dump(ud)
  for _,n in pairs(member_names) do print(n, ud[n]) end
end

print'*** b ***'
dump(b)

print'*** f ***'
dump(f)

print('b.name =', b.name, 'pos = ', b.x, b.y)
b.age = 88
b.x = 40
b.y = 50

print'*** modified b ***'
dump(b)

debug.debug()
