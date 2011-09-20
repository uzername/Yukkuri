require("data/scripts/adddebug")
---
Configs = {}
Configs.__index = Configs

function Configs.new()
	c = {}
	c.configs = {}
	setmetatable(c, Configs)
	return c
end

function Configs:load( filename )
	Debug(4, "Load " .. filename)
	local file, err = io.open(filename, "r")
	--- no print on assert. wtf?
	if file == nil then
		Debug(4, err .. ' in ' .. filename)
		return false
	end
	local filedata = file:read("*all")
	local data = assert(loadstring('return ' .. filedata))()
	file:close()
	ctype = string.lower(data[1])
	table.remove(data,1)
	for i,j in ipairs(data) do
		if self.configs[ctype] == nil then
			self.configs[ctype] = {}
		end
		if j.name == nil then
			Debug(4, i .. " in " .. filename ..  ": no name given. Skipped.")
			break
		end
		local name = string.lower(j.name)
		if self.configs[ctype][name] ~= nil then
			Debug(4, "Config with name " .. name .. " already loaded. Skipped.\n")
			break
		end
		self.configs[ctype][name] = j
	end
	return true
end

function Configs:loadAll( type )
	path = self:get("configs_path", "general", "general")
	if path == nil then
		path = getcwd() .. "/" .. "data/defs/"
	end
	listing = readdir(path)
	if listing == nil then
		Debug(4, "Bad directory " .. path)
		return
	end
	files = 0
	success = 0
	for i, filename in ipairs(listing) do
		if filename:match("%a+." .. type) then
			files = files + 1
			if self:load(path .. filename) then
				success = success + 1
			end
		end
	end
	Debug(4, "Loaded " .. success .. " from " .. files .. " config files")
end

function Configs:get( value, subconfig, config )
	ctype = string.lower(config)
	if self.configs[ctype] == nil then
		Debug(4, "Config " .. ctype .. " does not exist")
		return
	end
	csubtype = string.lower(subconfig)
	if self.configs[ctype][csubtype] == nil then
		Debug(4, "Subconfig " .. csubtype .. " not exists in config " .. ctype)
		return
	end
	ret = self.configs[ctype][csubtype][value]
	return ret
end

function Configs:getSubconfigs( config )
	t = {}
	for i,j in pairs(self.configs[string.lower(config)]) do
		table.insert(t, j)
	end
	return t
end

function Configs:getSubconfigsList( config )
	t = {}
	for i,j in pairs(self.configs[string.lower(config)]) do
		table.insert(t, i)
	end
	return t
end

function Configs:getSubconfigsLength( config )
	len = 0
	--- Я не смог в #
	for i in pairs(self.configs[string.lower(config)]) do
		len = len + 1
	end
	return len
end

function Configs:getOneFromSeveral( field, config )
	ctype = string.lower(config)
	config = self.configs[ctype]
	if config == nil then
		Debug(4, "Config " .. ctype .. " does not exist")
		return
	end
	local t = {}
	for i, j in pairs(config) do
		t[i] = config[i][field]
	end
	local min, max = 0.0, 0.0
	rnd = math.random()
	for i,j in pairs(t) do
		local el =  j / 100.0
		max = max + el
		if ( min < rnd and rnd <= max ) then
			return i
		end
	end
end

return Configs
