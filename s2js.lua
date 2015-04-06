local ffi = require("ffi")
local lpeg = require("lpeg")


lpeg.locale(lpeg) 

function maybe(p) return p^-1 end

setmetatable(_ENV or _G, { __index = lpeg or require"lpeg" })
  
local space = lpeg.space^0
-- wtf space
local br = (P"{" + P"}")
-- block descriptor
local text = R("az","AZ")^1

local number = R"09"

local type = P"struct" + P"class"
-- type of data
local sep = S";" * space
-- end of line 
local var = C(text*maybe(P("[")*space*(text+number+P'_')^1*space*P("]")+space*P"*"))*space*(C(text)*maybe(S",")*space)^0*sep
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
    C(type^1)* space * C(text)* space * br * Ct(Ct(space*var*space)^0) * br*space * sep * space
  )^1),result)

t = {}
for k,struct in pairs(structs) do
  --print(struct[2])
  t[struct[2]] = {}
  for k,prop in pairs(struct[3]) do
    local type
    for k,var in pairs(prop) do
      if k == 1 then
        type = var
      else
        local prop = '{"type":"'..type..'", "var": "' ..var..'"}'
        table.insert(t[struct[2]],prop)
        --print(prop)
      end
    end
  end
end

for k,v in pairs(t) do
  handler = io.open(k..".js","w")
  array = "module.exports = ["..table.concat(v,',').."]"
  handler:write(array)
  print(array)
  
end

