import tkinter as tk

class ToggleModule(tk.Frame):
    def __init__(self, parent, label_text, controller):
        super().__init__(parent)
        self.var = tk.IntVar()
        self.chk = tk.Checkbutton(self, text=label_text, variable=self.var, command=controller)
        self.chk.pack(anchor="w")

    def is_enabled(self):
        return bool(self.var.get())

    def label(self):
        return self.chk.cget("text")


class SentryControlPanel(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Sentry Control - BuckCheat Trial")
        self.geometry("440x400")
        self.resizable(False, False)

        self.modules = []
        self._init_layout()

    def _init_layout(self):
        # Top Branding
        branding = tk.Label(self, text="Sentry by BuckCheat", font=("Courier", 18, "bold"), fg="#004d00")
        branding.pack(pady=10)

        trial_notice = tk.Label(self, text="Trial Use: Valid for 7 Days", fg="#666666")
        trial_notice.pack()

        # Status Label
        self.status_label = tk.Label(self, text="System Idle", font=("Arial", 12), fg="darkred")
        self.status_label.pack(pady=15)

        # Modules
        module_frame = tk.Frame(self)
        module_frame.pack(pady=10, padx=20, fill="x")

        features = ["Auto Aim", "Wall Scan", "Zero Recoil", "Mini Radar"]
        for label in features:
            mod = ToggleModule(module_frame, label, self.refresh_status)
            mod.pack(anchor="w", pady=3)
            self.modules.append(mod)

        # Start Button
        btn = tk.Button(self, text="Start Sentry System", bg="#008000", fg="white", command=self.start_sentry)
        btn.pack(pady=20, ipadx=8, ipady=4)

    def refresh_status(self):
        enabled = [mod.label() for mod in self.modules if mod.is_enabled()]
        if enabled:
            msg = "Modules Active: " + ", ".join(enabled)
            self.status_label.config(text=msg, fg="green")
        else:
            self.status_label.config(text="System Idle", fg="darkred")

    def start_sentry(self):
        if any(mod.is_enabled() for mod in self.modules):
            self.status_label.config(text="Sentry System Engaged (Simulation)", fg="green")
        else:
            self.status_label.config(text="Enable at least one module first", fg="orange")


if __name__ == "__main__":
    SentryControlPanel().mainloop()