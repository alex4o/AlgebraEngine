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
bind = true
-- json output
t = {}
if bind then
for k,struct in pairs(structs) do
  print("value_object<" .. struct[2] .. '>("' .. struct[2] .. '")')
  t[struct[2]] = {}
  for k,prop in pairs(struct[3]) do
    local ti
    for k,var in pairs(prop) do
      if k == 1 then
        ti = var
      else
        print('.field("' .. var .. '",&' .. struct[2] .. '::' .. var .. ')')
        
      end

    end

  end
  print("----------")

end

--[[for k,v in pairs(t) do
  handler = io.open(arg[2]..k..".js","w")
  array = "module.exports = ["..table.concat(v,',').."]"
  handler:write(array)
  print("Saveing "..k..".js at "..arg[2])
  
end
]]

else
--json

for k,struct in pairs(structs) do
  print("var " .. struct[2] .. '= {')
  t[struct[2]] = {}
  for k,prop in pairs(struct[3]) do
    local ti
    for k,var in pairs(prop) do
      if k == 1 then
        ti = var
      else
        print(var .. ': 0,') 
      end

    end

  end
  print("}----------")

end


end


