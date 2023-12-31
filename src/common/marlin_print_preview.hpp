/**
 * @file marlin_print_preview.hpp
 * @brief state machine for print preview
 */
#pragma once
#include "gcode_info.hpp"
#include "client_response.hpp"

/**
 * @brief Parent class handling changes of state
 * Automatically changes fsm
 */
class IPrintPreview {
public:
    enum class State {
        inactive,

        init,
        download_wait,
        loading,
        preview_wait_user,

        unfinished_selftest_wait_user,

        new_firmware_available_wait_user,

        wrong_printer_wait_user,
        wrong_printer_wait_user_abort,

        filament_not_inserted_wait_user,
        filament_not_inserted_load,

        mmu_filament_inserted_wait_user,
        mmu_filament_inserted_unload,

        tools_mapping_wait_user,

        wrong_filament_wait_user,
        wrong_filament_change,
        checks_done,

        done,
    };

private:
    State state = State::inactive;
    std::optional<PhasesPrintPreview> phase = std::nullopt;

    static std::optional<PhasesPrintPreview> getCorrespondingPhase(State state);
    void setFsm(std::optional<PhasesPrintPreview> wantedPhase);

public:
    void ChangeState(State s);

    inline State GetState() const {
        return state;
    }
    Response GetResponse();
};

class PrintPreview : public IPrintPreview {

    static constexpr uint32_t max_run_period_ms = 50;
    static constexpr uint32_t DOWNLOAD_CHECK_PERIOD = 2000;
    uint32_t new_firmware_open_ms { 0 };
    static constexpr uint32_t new_firmware_timeout_ms { 30000 }; // three seconds
public:
    enum class Result {
        Wait,
        // Showing the image and asking if print.
        Image,
        // Asking the user something (wrong printer, etc).
        Questions,
        ToolsMapping,
        MarkStarted,
        Abort,
        Print,
        Inactive
    };

    static PrintPreview &Instance() {
        static PrintPreview ret;
        return ret;
    }

    /**
     * @brief Handles cleanup required by leaving tools_mapping screen.
     *
     * @param leaving_to_print Some cleanup is dependant whether the screen is left to go print or whether it's being left 'back home'
     */
    static void tools_mapping_cleanup(bool leaving_to_print = false);

    Result Loop();

    void Init();
    void SkipIfAble() { skip_if_able = true; }
    void DontSkip() { skip_if_able = false; }
    /**
     * @brief Checks whether the given physical extruder has corrent filament type for the print. Parametrized with getter to be callable without global tool_mapper/spool_join being in a valid state
     *
     * @param physical_extruder extruder to be checked
     * @param no_gcode_value Return value of gcode_extruder_getter if physical_extruder doesn't print anything
     * @param gcode_extruder_getter Call to get assigned gcode extruder to physical_extruder
     */
    static bool check_correct_filament_type(uint8_t physical_extruder, uint8_t no_gcode_value, std::function<uint8_t(uint8_t)> gcode_extruder_getter);

    /**
     * @brief Checks whether given physical extruder needs to have a filament loaded -> if it's used in a print and not loaded, then it needs to load. nt. Parametrized with getter to be callable without global tool_mapper/spool_join being in a valid state
     *
     * @param physical_extruder extruder to be checked
     * @param no_gcode_value Return value of gcode_extruder_getter if physical_extruder doesn't print anything
     * @param gcode_extruder_getter Call to get assigned gcode extruder to physical_extruder
     */
    static bool check_extruder_need_filament_load(uint8_t physical_extruder, uint8_t no_gcode_value, std::function<uint8_t(uint8_t)> gcode_extruder_getter);

private:
    uint32_t last_run = 0;
    uint32_t last_download_check = 0;

    bool skip_if_able = false;

    PrintPreview() = default;
    PrintPreview(const PrintPreview &) = delete;

    State stateFromFilamentPresence() const;
    State stateFromFilamentType() const;

    State stateFromSelftestCheck();
    State stateFromUpdateCheck();
    State stateFromPrinterCheck();
    Result stateToResult() const;
};
