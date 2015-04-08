local ffi = require("ffi")
local lpeg = require("lpeg")


lpeg.locale(lpeg) 



setmetatable(_ENV or _G, { __index = lpeg or require"lpeg" })

function maybe(p) return p^-1 end

local space = lpeg.space^0
-- wtf space
local br = (P"{" + P"}")
-- block descriptor
local text = R("az","AZ")^1

local number = R"09"

local ti = P"struct" + P"class"
-- type of data
local sep = S";" * space
-- end of line 
local var = C(
  text*maybe(space*P"*")
  )*space*(
    C(text)
    *maybe(P("[")*space*C(number^0)*space*P("]"))
    *maybe(S",")*space
  )^0*sep
-- get the struct properties 
local tag = S'"<>' 
--include definition tags
local include = P("#include")*space*C(tag*(text+P".")^1*tag)
--parses include statements

handle = io.popen("gcc -E -P " .. arg[1])
local result = handle:read("*a")
handle:close()

structs = match(
  Ct(space*
  Ct(
    C(ti^1)* space * C(text)* space * br * Ct(Ct(space*var*space)^0) * br*space * sep * space
  )^1),result)

type_c = {
  int = "long",
  bool = "boolean",
  char = "byte",
}
json = false
-- json output
t = {}
if json then
for k,struct in pairs(structs) do
  --print(struct[2])
  t[struct[2]] = {}
  for k,prop in pairs(struct[3]) do
    local ti
    for k,var in pairs(prop) do
      if k == 1 then
        ti = var
      else
        local prop = '{"type":"'..type..'", "var": "' ..var..'"}'
        table.insert(t[struct[2]],prop)
        --print(prop)
      end
    end
  end
end

for k,v in pairs(t) do
  handler = io.open(arg[2]..k..".js","w")
  array = "module.exports = ["..table.concat(v,',').."]"
  handler:write(array)
  print("Saveing "..k..".js at "..arg[2])
  
end

else
--web idl


for k,struct in pairs(structs) do
  t[struct[2]] = {}
  type_c[struct[2]] = k
  for k,prop in pairs(struct[3]) do
    local ti --tyepof prop
    for k,var in pairs(prop) do
      if k == 1 then
        ti = var
      else
        --print(ti)
        local pres = type_c[ti]
        print(type(prop[k+1]))
        if lpeg.match(number^1,type(k+1)) ~= nill then
          pres = pres .. "["..prop[k+1].."]"..' '..var..';'
          
          --print(prop)
        else
          pres = pres..' '..var..';'
        end
        table.insert(t[struct[2]],pres)
      end
    end
  end
end

for k,v in pairs(t) do
  handler = io.open(arg[2]..k..".idl","w")
  array = "interface "..k.." {\n"..table.concat(v,'\n').."\n}"
  print(array)
  print("Saveing "..k..".idl at "..arg[2])
  
end
end

ffi.cdef[[
  struct a{
    int b;
  }
]]

a = ffi.new('struct a', 12)

