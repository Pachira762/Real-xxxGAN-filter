#include "pch.h"
#include "real-xxxgan-filter.h"

static RealXxxGanFilter* plugin = nullptr;

static constexpr int NumTrackbarItems = 4;
static TCHAR* TrackbarNames[NumTrackbarItems] = { "モード", "スケール", "デノイズ", "TTA" };
static int TrackbarDefaults[NumTrackbarItems] = { 0, 2, -1, 0 };
static int TrackbarMins[NumTrackbarItems] = { 0, 1, -1, 0 };
static int TrackbarMaxs[NumTrackbarItems] = { 3, 4, 3, 1 };

BOOL InitPlugin(FILTER* fp) {
	if (plugin) {
		delete plugin;
	}

	plugin = new RealXxxGanFilter();

	return TRUE;
}

BOOL ExitPlugin(FILTER* fp) {
	if (plugin) {
		delete plugin;
		plugin = nullptr;
	}

	return TRUE;
}

BOOL ProcPlugin(FILTER* fp, FILTER_PROC_INFO* fpip) {
	if (!plugin) {
		return FALSE;
	}

	Mode mode = (Mode)fp->track[0];
	int scale = fp->track[1];
	int denoise = fp->track[2];
	bool tta = fp->track[3];

	int w = fpip->w;
	int h = fpip->h;
	int w_max = fpip->max_w;
	int h_max = fpip->max_h;
	int w_out = std::min(w_max, scale * w);
	int h_out = std::min(h_max, scale * h);

	if (!plugin->SetSize(w, h, scale)) {
		MessageBoxW(NULL, L"Failed buffer allocation!\n", L"Real-xxxGAN-filter", MB_OK);
		return FALSE;
	}

	for (int y = 0; y < h; ++y) {
		auto yc = &fpip->ycp_edit[w_max * y];
		auto bgra = &plugin->GetInputBuffer()[4 * w * y];

		for (int x = 0; x < w; ++x) {
			fp->exfunc->yc2rgb((PIXEL*)bgra, yc, 1);
			bgra[3] = 0xff;

			yc += 1;
			bgra += 4;
		}
	}

	if (!plugin->Process(mode, scale, denoise, tta)) {
		return FALSE;
	}

	for (int y = 0; y < h_out; ++y) {
		auto yc = &fpip->ycp_edit[w_max * y];
		auto bgra = &plugin->GetOutputBuffer()[4 * scale * w * y];

		for (int x = 0; x < w_out; ++x) {
			fp->exfunc->rgb2yc(yc, (PIXEL*)bgra, 1);

			yc += 1;
			bgra += 4;
		}
	}

	fpip->w = w_out;
	fpip->h = h_out;

	return TRUE;
}

EXTERN_C __declspec(dllexport) FILTER_DLL* __stdcall GetFilterTable(void) {
	static FILTER_DLL dll{};

	dll.flag = FILTER_FLAG_EX_INFORMATION;
	dll.name = "Real-xxxGAN-filter";
	dll.track_n = NumTrackbarItems;
	dll.track_name = TrackbarNames;
	dll.track_default = TrackbarDefaults;
	dll.track_s = TrackbarMins;
	dll.track_e = TrackbarMaxs;
	dll.func_proc = ProcPlugin;
	dll.func_init = InitPlugin;
	dll.func_exit = ExitPlugin;
	dll.information = "モード 0:Real-CUGAN 1:Real-ESRGAN-AnimeVideo-v3 2:Real-ESRGAN-x4plus 3:Real-ESRGAN-4plus-Anime";

	return &dll;
}