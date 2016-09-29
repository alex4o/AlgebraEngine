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

function print_r ( t )  
    local print_r_cache={}
    local function sub_print_r(t,indent)
        if (print_r_cache[tostring(t)]) then
            print(indent.."*"..tostring(t))
        else
            print_r_cache[tostring(t)]=true
            if (type(t)=="table") then
                for pos,val in pairs(t) do
                    if (type(val)=="table") then
                        print(indent.."["..pos.."] => "..tostring(t).." {")
                        sub_print_r(val,indent..string.rep(" ",string.len(pos)+8))
                        print(indent..string.rep(" ",string.len(pos)+6).."}")
                    elseif (type(val)=="string") then
                        print(indent.."["..pos..'] => "'..val..'"')
                    else
                        print(indent.."["..pos.."] => "..tostring(val))
                    end
                end
            else
                print(indent..tostring(t))
            end
        end
    end
    if (type(t)=="table") then
        print(tostring(t).." {")
        sub_print_r(t,"  ")
        print("}")
    else
        sub_print_r(t,"  ")
    end
    print()
end
 


type_c = {
  int = "long",
  bool = "boolean",
  char = "byte",
}
bind = false
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
  print("\n----------")

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

t = {}

function print_json(struct, inside)
  if inside then
    print('{')
    
  else
    print("var " .. struct[2] .. '= {')
  end

  
  t[struct[2]] = struct

  for k,prop in pairs(struct[3]) do
    local ti
    for k,var in pairs(prop) do
      if k == 1 then
        ti = var
      else

        if t[ti] == nil then 
          print("\t" .. var .. ': "' .. ti .. '",') 
        else
          print("\t" .. var .. ':') 
          print_json(t[ti], true)
        end
      end

    end
  end

  if inside then
    print('},')
    
  else
    print("}\n\n")

  end


end

for k,struct in pairs(structs) do
  print_json(struct)
end


end

--print_r(structs)

