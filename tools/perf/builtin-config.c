/*
 * builtin-config.c
 *
 * Copyright (C) 2015, Taeung Song <treeze.taeung@gmail.com>
 *
 */
#include "builtin.h"

#include "perf.h"

#include "util/cache.h"
#include "util/parse-options.h"
#include "util/util.h"
#include "util/debug.h"

static const char * const config_usage[] = {
	"perf config [options]",
	NULL
};

enum actions {
	ACTION_LIST = 1
} actions;

static const struct option config_options[] = {
	OPT_GROUP("Action"),
	OPT_SET_UINT('l', "list", &actions,
		     "show current config variables", ACTION_LIST),
	OPT_END()
};

static int show_config(const char *key, const char *value,
		       void *cb __maybe_unused)
{
	if (value)
		printf("%s=%s\n", key, value);
	else
		printf("%s\n", key);

	return 0;
}

int cmd_config(int argc, const char **argv, const char *prefix __maybe_unused)
{
	int ret = 0;

	argc = parse_options(argc, argv, config_options, config_usage,
			     PARSE_OPT_STOP_AT_NON_OPTION);

	switch (actions) {
	case ACTION_LIST:
	default:
		if (argc) {
			pr_err("Error: unknown argument\n");
			usage_with_options(config_usage, config_options);
		} else
			ret = perf_config(show_config, NULL);
	}

	return ret;
}
