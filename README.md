# block_state_converter
Convert runtime_block_states*.json from steadfast to more simplified format and use on other platforms.



##

### Example for Nukkit:
```Java
    @Deprecated
    private static void setupFromSteadFast() {
        InputStream stream = Server.class.getClassLoader().getResourceAsStream("runtime_block_states.json");
        if (stream == null) throw new AssertionError("Unable to locate block state");
        Collection<SteadFastEntry> entries = new Gson().fromJson(new InputStreamReader(stream, StandardCharsets.UTF_8), new TypeToken<Collection<SteadFastEntry>>(){}.getType());
        for (SteadFastEntry entry : entries) {
            int legacyId = entry.id << 6 | entry.data;
            legacyToRuntimeId.put(legacyId, entry.runtimeId);
        }
    }

    @Deprecated
    public static class SteadFastEntry {
        private int id;
        private int data;
        private int runtimeId;
    }
