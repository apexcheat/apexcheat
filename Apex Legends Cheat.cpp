#include <QApplication>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QWidget>
#include <QStringList>

class SentryPanel : public QWidget {
    Q_OBJECT

public:
    SentryPanel(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("Sentry - BuckCheat Trial");
        setFixedSize(420, 400);

        // Branding
        QLabel *title = new QLabel("🛡️ Sentry by BuckCheat");
        title->setStyleSheet("font-weight: bold; font-size: 20px; color: #006400;");
        title->setAlignment(Qt::AlignCenter);

        QLabel *trial = new QLabel("Trial Mode: 7 Days Remaining");
        trial->setStyleSheet("color: gray;");
        trial->setAlignment(Qt::AlignCenter);

        statusLabel = new QLabel("🛑 System Idle");
        statusLabel->setStyleSheet("color: darkred; font-size: 14px;");
        statusLabel->setAlignment(Qt::AlignCenter);

        // Features
        QGroupBox *featureBox = new QGroupBox("Sentry Modules");
        QVBoxLayout *featureLayout = new QVBoxLayout;

        aimbot = new QCheckBox("Auto Aim");
        wallscan = new QCheckBox("Wall Scan");
        norecoil = new QCheckBox("Zero Recoil");
        radar = new QCheckBox("Mini Radar");

        featureLayout->addWidget(aimbot);
        featureLayout->addWidget(wallscan);
        featureLayout->addWidget(norecoil);
        featureLayout->addWidget(radar);
        featureBox->setLayout(featureLayout);

        connect(aimbot, &QCheckBox::stateChanged, this, &SentryPanel::updateStatus);
        connect(wallscan, &QCheckBox::stateChanged, this, &SentryPanel::updateStatus);
        connect(norecoil, &QCheckBox::stateChanged, this, &SentryPanel::updateStatus);
        connect(radar, &QCheckBox::stateChanged, this, &SentryPanel::updateStatus);

        // Start Button
        QPushButton *startBtn = new QPushButton("🚀 Launch Sentry");
        startBtn->setStyleSheet("background-color: green; color: white; font-size: 14px;");
        connect(startBtn, &QPushButton::clicked, this, &SentryPanel::startSentry);

        // Main Layout
        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->addWidget(title);
        mainLayout->addWidget(trial);
        mainLayout->addSpacing(10);
        mainLayout->addWidget(statusLabel);
        mainLayout->addSpacing(10);
        mainLayout->addWidget(featureBox);
        mainLayout->addSpacing(10);
        mainLayout->addWidget(startBtn);

        setLayout(mainLayout);
    }

private slots:
    void updateStatus() {
        QStringList active;

        if (aimbot->isChecked()) active << "Auto Aim";
        if (wallscan->isChecked()) active << "Wall Scan";
        if (norecoil->isChecked()) active << "Zero Recoil";
        if (radar->isChecked()) active << "Mini Radar";

        if (!active.isEmpty()) {
            statusLabel->setText("✅ Active Modules: " + active.join(", "));
            statusLabel->setStyleSheet("color: green; font-size: 14px;");
        } else {
            statusLabel->setText("🛑 System Idle");
            statusLabel->setStyleSheet("color: darkred; font-size: 14px;");
        }
    }

    void startSentry() {
        if (aimbot->isChecked() || wallscan->isChecked() || norecoil->isChecked() || radar->isChecked()) {
            statusLabel->setText("✅ Sentry System Engaged (Demo)");
            statusLabel->setStyleSheet("color: green; font-size: 14px;");
        } else {
            statusLabel->setText("⚠️ Enable at least one module first");
            statusLabel->setStyleSheet("color: orange; font-size: 14px;");
        }
    }

private:
    QLabel *statusLabel;
    QCheckBox *aimbot;
    QCheckBox *wallscan;
    QCheckBox *norecoil;
    QCheckBox *radar;
};

#include "sentry_panel.moc"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    SentryPanel panel;
    panel.show();
    return app.exec();
}