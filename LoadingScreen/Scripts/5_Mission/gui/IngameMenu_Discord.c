static const float DISCORD_BUTTON_OFFSET = 0.005;

class DiscordConfig
{
    string DiscordUrl;
};

static string g_DiscordUrl;
static bool g_DiscordUrlLoaded;

static string GetDiscordUrl()
{
    if (!g_DiscordUrlLoaded)
    {
        g_DiscordUrlLoaded = true;
        DiscordConfig cfg;
        if (FileExist("LoadingScreen/Config/DiscordSettings.json"))
        {
            JsonFileLoader<DiscordConfig>.JsonLoadFile("LoadingScreen/Config/DiscordSettings.json", cfg);
            if (cfg && cfg.DiscordUrl != string.Empty)
            {
                g_DiscordUrl = cfg.DiscordUrl;
            }
            else
            {
                Print("[DiscordButton] Invalid or empty DiscordUrl");
            }
        }
        else
        {
            Print("[DiscordButton] LoadingScreen/Config/DiscordSettings.json not found");
        }
    }
    return g_DiscordUrl;
}

static ButtonWidget FindAnyButton(Widget root)
{
    if (!root)
        return null;

    Widget child = root.GetChildren();
    while (child)
    {
        ButtonWidget btn = ButtonWidget.Cast(child);
        if (btn)
            return btn;

        ButtonWidget sub = FindAnyButton(child);
        if (sub)
            return sub;

        child = child.GetSibling();
    }
    return null;
}

modded class IngameMenu extends UIScriptedMenu
{
    protected ButtonWidget m_DiscordBtn;

    override Widget Init()
    {
        Widget root = super.Init();
        CreateDiscordButton(root);
        return root;
    }

    override void OnShow()
    {
        super.OnShow();
        CreateDiscordButton(m_Root);
    }

    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (w == m_DiscordBtn)
        {
            string url = GetDiscordUrl();
            if (url != string.Empty)
                GetGame().OpenURL(url);
            return true;
        }
        return super.OnClick(w, x, y, button);
    }

    protected void CreateDiscordButton(Widget root)
    {
        if (!root || m_DiscordBtn)
            return;

        ButtonWidget model = FindAnyButton(root);
        if (!model)
        {
            Print("[DiscordButton] Model button not found");
            return;
        }

        Widget parent = model.GetParent();
        if (!parent)
            return;

        m_DiscordBtn = ButtonWidget.Cast(model.Clone(parent));
        if (!m_DiscordBtn)
            return;

        m_DiscordBtn.SetName("btn_discord");
        m_DiscordBtn.SetText("Discord");
        m_DiscordBtn.SetHandler(this);

        float x, y, w, h;
        float lastBottom = 0;
        float baseX = 0;
        Widget child = parent.GetChildren();
        while (child)
        {
            ButtonWidget btn = ButtonWidget.Cast(child);
            if (btn)
            {
                btn.GetPos(x, y);
                btn.GetSize(w, h);
                float bottom = y + h;
                if (bottom > lastBottom)
                {
                    lastBottom = bottom;
                    baseX = x;
                }
            }
            child = child.GetSibling();
        }

        m_DiscordBtn.SetPos(baseX, lastBottom + DISCORD_BUTTON_OFFSET);
    }
}

modded class ExpansionIngameMenu extends UIScriptedMenu
{
    protected ButtonWidget m_DiscordBtn;

    override Widget Init()
    {
        Widget root = super.Init();
        CreateDiscordButton(root);
        return root;
    }

    override void OnShow()
    {
        super.OnShow();
        CreateDiscordButton(m_Root);
    }

    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (w == m_DiscordBtn)
        {
            string url = GetDiscordUrl();
            if (url != string.Empty)
                GetGame().OpenURL(url);
            return true;
        }
        return super.OnClick(w, x, y, button);
    }

    protected void CreateDiscordButton(Widget root)
    {
        if (!root || m_DiscordBtn)
            return;

        ButtonWidget model = FindAnyButton(root);
        if (!model)
        {
            Print("[DiscordButton] Model button not found");
            return;
        }

        Widget parent = model.GetParent();
        if (!parent)
            return;

        m_DiscordBtn = ButtonWidget.Cast(model.Clone(parent));
        if (!m_DiscordBtn)
            return;

        m_DiscordBtn.SetName("btn_discord");
        m_DiscordBtn.SetText("Discord");
        m_DiscordBtn.SetHandler(this);

        float x, y, w, h;
        float lastBottom = 0;
        float baseX = 0;
        Widget child = parent.GetChildren();
        while (child)
        {
            ButtonWidget btn = ButtonWidget.Cast(child);
            if (btn)
            {
                btn.GetPos(x, y);
                btn.GetSize(w, h);
                float bottom = y + h;
                if (bottom > lastBottom)
                {
                    lastBottom = bottom;
                    baseX = x;
                }
            }
            child = child.GetSibling();
        }

        m_DiscordBtn.SetPos(baseX, lastBottom + DISCORD_BUTTON_OFFSET);
    }
}
